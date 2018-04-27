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

#include "history.h"

void history_init(history_t **node, state_t *state) {
    *node = (history_t *) malloc(sizeof(history_t));

    (*node)->state = state;
    (*node)->next = NULL;
    (*node)->prev = NULL;
    (*node)->length = 1;
    (*node)->move = -1;
}

void history_destroy(history_t *node) {
    if (node == NULL)
        return;

    if (node->state != NULL)
        state_destroy(node->state);

    if (node->next != NULL)
        history_destroy(node->next);

    free(node);
}

void history_push(history_t *node, int move, state_t *state) {
    history_t *last = _history_last_node(node);

    history_t *new_node;
    history_init(&new_node, state);
    last->next = new_node;
    last->move = move;
    new_node->prev = last;

    _history_update_lengths(last);
}

state_t *history_pop(history_t *node) {
    history_t *tmp = _history_last_node(node);
    state_t *out = tmp->state;

    history_t *prev = tmp->prev;

    tmp->state = NULL;
    prev->next = NULL;

    history_destroy(tmp);
    _history_update_lengths(node);
    return out;
}

history_t *_history_last_node(history_t *node) {
    history_t *tmp = node;

    while (tmp->next != NULL)
        tmp = tmp->next;

    return tmp;
}

void _history_update_lengths(history_t *node) {
    history_t *tmp = _history_last_node(node);

    while (tmp != NULL) {
        if (tmp->next == NULL) {
            tmp->length = 0;
        } else {
            history_t *n = tmp->next;
            tmp->length = n->length + 1;
        }

        tmp = tmp->prev;
    }
}