/**

    MIT License

    Copyright (c) 2018 Berke Emrecan ARSLAN

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.

 */

#include <gtk/gtk.h>
#include <pthread.h>
#include "gui.h"
#include "../game/board.h"
#include "../game/state.h"
#include "../game/history.h"
#include "../engine/mcts.h"

GtkWidget *window;

static gboolean update_button_label(gpointer userdata) {
    gui_action_t* data = (gui_action_t*) userdata;

    char *s = (char*) malloc(sizeof(char) * 2);
    bzero(s, 2);
    sprintf(s, "%c", data->turn);

    gtk_button_set_label(GTK_BUTTON(buttons[data->action]), s);
    gtk_widget_set_sensitive(buttons[data->action], FALSE);

    return G_SOURCE_REMOVE;
}

static gboolean disable_buttons(gpointer userdata) {
    int i;
    for(i = 0; i < 9; i++) {
        gtk_widget_set_sensitive(buttons[i], FALSE);
    }
}

static gboolean enable_buttons(gpointer userdata) {
    int i;
    for(i = 0; i < 9; i++) {
        if(strlen(gtk_button_get_label(GTK_BUTTON(buttons[i]))) > 0)
            continue;

        gtk_widget_set_sensitive(buttons[i], TRUE);
    }

    return G_SOURCE_REMOVE;
}

static gboolean clear_buttons(gpointer userdata) {
    int i;
    for(i = 0; i < 9; i++) {
        gtk_button_set_label(GTK_BUTTON(buttons[i]), "");
    }

    enable_buttons(NULL);
}

static void on_dialog_again_response(GtkDialog* dialog, gint response_id, gpointer user_data) {
    if(response_id == GTK_RESPONSE_OK) {
        clear_buttons(NULL);
    } else if(response_id == GTK_RESPONSE_CANCEL) {
        // @TODO: do something with it :D
    }

    gtk_widget_destroy(GTK_WIDGET(dialog));
}

static gboolean ask_again(gpointer userdata) {
    game_result_t* question = (game_result_t*)userdata;
    GtkWidget *msg_dialog;
    GtkWindow *parent = (GtkWindow*) window;
    GtkDialogFlags flags = GTK_DIALOG_DESTROY_WITH_PARENT;

    msg_dialog = gtk_message_dialog_new(parent,
                                        flags,
                                        GTK_MESSAGE_QUESTION,
                                        GTK_BUTTONS_OK_CANCEL,
                                        "%s",
                                        question->msg);

    gtk_widget_show_all(msg_dialog);
    g_signal_connect(GTK_DIALOG(msg_dialog), "response", G_CALLBACK(on_dialog_again_response), NULL);

    return G_SOURCE_REMOVE;
}

void* gui_loop(void* p) {
    while(1) {
        state_t *cstate;
        history_t *hist;

        state_init(&cstate);
        history_init(&hist, cstate);

        char status = PE;
        while(status == PE) {
            g_main_context_invoke(NULL, disable_buttons, NULL);

            int a;
            if(cstate->turn == P1) {
                g_main_context_invoke(NULL, enable_buttons, NULL);
                while (gui_action.wait)
                    usleep(1000);

                a = gui_action.action;

                pthread_mutex_lock(&gui_action_mutex);
                gui_action.action = -1;
                gui_action.wait = 1;
                pthread_mutex_unlock(&gui_action_mutex);
            } else {
                a = mcts_genmove(cstate, P2);
            }

            gui_action_t ga;

            ga.action = a;
            ga.turn = cstate->turn;

            g_main_context_invoke (NULL, update_button_label, &ga);

            cstate = state_advance(cstate, a);

            history_push(hist, a, cstate);
            status = state_status(cstate);
        }

        game_result_t *gr = (game_result_t*) malloc(sizeof(game_result_t));
        gr->msg = (char*) malloc(sizeof(char) * 128);
        bzero(gr->msg, 128);

        switch(status) {
            case P1:
            case P2:
                sprintf(gr->msg, "%c won! Again?", status);
                break;
            case PD:
            default:
                sprintf(gr->msg, "Draw! Again?");
                break;
        }

        g_main_context_invoke(NULL, ask_again, gr);

        history_destroy(hist);
    }
}

void create_game_thread() {
    pthread_t game_thr;
    pthread_attr_t game_thr_attr;

    gui_action.wait = 1;
    gui_action.action = -1;

    pthread_mutex_init(&gui_action_mutex, NULL);
    pthread_attr_init(&game_thr_attr);
    pthread_attr_setdetachstate(&game_thr_attr, PTHREAD_CREATE_JOINABLE);
    pthread_create(&game_thr, &game_thr_attr, gui_loop, NULL);
    pthread_attr_destroy(&game_thr_attr);
    enable_buttons(NULL);
}

static int get_button_index(GtkWidget *button) {
    int i;
    for(i = 0; i < 9; i++) {
        if(button == buttons[i])
            return i;
    }

    return -1;
}

void button_click(GtkWidget *widget, gpointer data) {
    pthread_mutex_lock(&gui_action_mutex);
    gui_action.action = get_button_index(widget);
    gui_action.wait = 0;
    pthread_mutex_unlock(&gui_action_mutex);
}

static void activate(GtkApplication *app, gpointer user_data) {
    int i, j;
    GtkWidget *grid;
    buttons = (GtkWidget**) malloc(sizeof(GtkWidget*) * 9);

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Felix TTT");
    gtk_window_set_default_size(GTK_WINDOW(window), 200, 150);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);

    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            char *s = (char *) malloc(sizeof(char) * 2);
            sprintf(s, "");
            buttons[i*3+j] = gtk_button_new_with_label(s);
            gtk_container_set_border_width(GTK_CONTAINER(buttons[i*3+j]), 5);
            g_signal_connect(buttons[i*3+j], "clicked", G_CALLBACK(button_click), NULL);
            gtk_grid_attach(GTK_GRID(grid), buttons[i*3+j], j, 3 * i, 1, 3);
        }
    }

    create_game_thread();
    gtk_widget_show_all(window);
}

int main(int argc, char **argv) {
    int status;

    GtkApplication *app;

    app = gtk_application_new("com.beremaran.felix_ttt", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);

    g_object_unref(app);
    pthread_mutex_destroy(&gui_action_mutex);
    return status;
}
