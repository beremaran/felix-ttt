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

#ifndef FELIX_TTT_HISTORY_H
#define FELIX_TTT_HISTORY_H

#include <stdlib.h>
#include "state.h"

/**
 *
 */
typedef struct _history_t history_t;

/**
 *
 */
struct _history_t {
    int move;
    size_t length;
    state_t *state;
    history_t *next;
    history_t *prev;
};

/**
 *
 * @param node
 * @param state
 */
void history_init(history_t **node, state_t *state);

/**
 *
 * @param node
 */
void history_destroy(history_t *node);

/**
 *
 * @param node
 * @param state
 */
void history_push(history_t *node, int move, state_t *state);

/**
 *
 * @param node
 * @return
 */
state_t *history_pop(history_t *node);

/**
 *
 * @param node
 * @return
 */
history_t *_history_last_node(history_t *node);

/**
 *
 * @param node
 */
void _history_update_lengths(history_t *node);

#endif //FELIX_TTT_HISTORY_H
