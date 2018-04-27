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

#include <stdlib.h>
#include <strings.h>
#include "tree.h"
#include "../utils/binarysearch.h"

void tree_init(node_t **node, node_t *parent, char by_action, state_t *state) {
    static node_t *_null_node = NULL;

    if (_null_node == NULL) {
        _null_node = (node_t *) malloc(sizeof(node_t));
        _null_node->__null_node = 1;
    }

    int i;
    node_t *n = *node = (node_t *) malloc(sizeof(node_t));

    n->q = 0;
    n->state = state;
    n->parent = parent;
    n->plays = 0;
    n->score = 0;
    n->n_children = 0;
    n->__null_node = 0;
    n->by_action = by_action;

    n->children = (node_t **) malloc(sizeof(node_t *) * BOARD_SIZE);

    int available_action_n;
    int *available_actions = NULL;
    board_legal_actions(state->board, &available_actions, &available_action_n);
    for (i = 0; i < BOARD_SIZE; i++) {
        n->children[i] = NULL;
    }

    free(available_actions);

    if (parent != NULL) {
        parent->children[by_action] = n;
        parent->n_children++;
    }
}

void tree_destroy(node_t *node) {
    int i;
    state_destroy(node->state);

    node_t **ch = node->children;
    for (i = 0; i < BOARD_SIZE; i++) {
        if (ch[i] != NULL) {
            tree_destroy(ch[i]);
        }
    }

    free(node->children);
    free(node);
}