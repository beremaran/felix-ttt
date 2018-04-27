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
#include <stdio.h>
#include "ascii.h"
#include "../tgf/tgf.h"
#include "../game/state.h"
#include "../engine/mcts.h"
#include "../game/history.h"
#include "../engine/random.h"

void ascii_loop() {

    printf("ASCII interface initializing ..\n");
    // ===
    state_t *cstate;
    history_t *hist;

    state_init(&cstate);
    history_init(&hist, cstate);
    //random_init();

    // ===
    printf("Done.\n\n");
    // ===

    char status = PE;
    while (status == PE) {
        printf(" Move #%ld", hist->length);
        ascii_print_state(cstate);

        int a;
        if (cstate->turn == P1) {

            a = ascii_request_input();
            if (a == -1) {
                fprintf(stderr, "\nIllegal move!\n\n");
                continue;
            }

            //a = mcts_genmove(cstate, P1);
        } else {
            //a = random_genmove(cstate);
            a = mcts_genmove(cstate, P2);
        }

        cstate = state_advance(cstate, a);
        history_push(hist, a, cstate);
        status = state_status(cstate);
    }

    tgf_dump_history(hist, "history.tgf");
    ascii_print_endgame(cstate);
    history_destroy(hist);
}

void ascii_print_board(char *board) {
    int i, j;

    for (i = 0; i < 3; i++) {

        printf("%3s", "");

        for (j = 0; j < 3; j++) {
            printf("%c ", board[3 * i + j]);
        }

        printf("%3s", "");

        for (j = 0; j < 3; j++) {
            if (board[3 * i + j] == PE) {
                printf("%d", 3 * i + j);
            } else {
                printf(".");
            }

            printf(" ");
        }

        printf("\n");
    }
}

void ascii_print_state(state_t *state) {
    int i;

    printf("\n%2s%c plays\n", "", state->turn);
    ascii_print_board(state->board);
    printf("\nAvailable actions: ");

    for (i = 0; i < state->available_move_n; i++) {
        printf("%2d ", state->available_moves[i]);
    }
    printf("\n");
}

void ascii_print_endgame(state_t *state) {
    char s = state_status(state);
    switch (s) {
        case P1:
        case P2:
            printf("\n%2s%c wins!\n", "", state_next_player(state));
            break;
        case PD:
            printf("\n%2sDraw!\n", "");
            break;
        default:
        case PE:
            fprintf(stderr, "? GAME IS NOT FINISHED ?\n");

    }

    ascii_print_board(state->board);
}

int ascii_request_input() {
    int c;
    char inp;
    printf("? > ");

    scanf("%c", &inp);

    inp -= 48;
    if (inp < 0 || inp >= 9) {
        return -1;
    }

    while ((c = getchar()) != '\n' && c != EOF) {}
    return inp;
}
