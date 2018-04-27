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

#ifndef FELIX_TTT_TREE_H
#define FELIX_TTT_TREE_H

#include <stdlib.h>
#include <stdint.h>
#include "../game/state.h"

/**
 *
 */
typedef struct _tree_node node_t;
struct _tree_node {
    state_t *state;

    node_t *parent;
    node_t **children;
    size_t n_children;

    uint64_t plays;
    int64_t score;

    long double q;

    char by_action;
    char __null_node;
};

/**
 *
 * @param node
 * @param parent
 * @param state
 */
void tree_init(node_t **node, node_t *parent, char by_action, state_t *state);

/**
 *
 * @param node
 */
void tree_destroy(node_t *node);

#endif //FELIX_TTT_TREE_H
