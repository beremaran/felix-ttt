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
#include <math.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include "mcts.h"
#include "random.h"
#include "../interface/ascii.h"


int mcts_genmove(state_t *state, char player) {
    if (state->available_move_n == 1) {
        return state->available_moves[0];
    }

    int selected_action;
    int64_t outcome;
    uint32_t total_sims = 0;
    node_t *root, *selected;
    struct timespec start, now;

    // init mersenne twister
    random_init();

    // create root node
    tree_init(&root, NULL, PD, state);

    // run until time is up
    clock_gettime(CLOCK_MONOTONIC, &start);
    clock_gettime(CLOCK_MONOTONIC, &now);
    while ((now.tv_sec - start.tv_sec) < MCTS_TIME_LIMIT) {
        // select most promising child by ucb policy
        selected = _mcts_descend(root, total_sims);
        // playout uniformly random
        outcome = _mcts_random_playout(selected, player);
        // update tree values
        _mcts_backpropagate(selected, outcome);

        // update current time
        clock_gettime(CLOCK_MONOTONIC, &now);
        // completed another simulation
        total_sims++;
    }

    int i;
    for (i = 0; i < BOARD_SIZE; i++) {
        if (root->children[i] == NULL)
            continue;
    }

    // return best child of root
    selected = _mcts_best_child(root, total_sims);
    selected_action = selected->by_action;
    for (i = 0; i < BOARD_SIZE; i++)
        if (root->children[i] != NULL)
            tree_destroy(root->children[i]);

    return selected_action;
}

node_t *_mcts_descend(node_t *root, uint32_t total_sims) {
    node_t *tmp = root;
    state_t *s = tmp->state;

    while (state_status(s) == PE) {
        if (tmp->n_children == 0) {
            return _mcts_expand(tmp);
        }

        tmp = _mcts_best_child(tmp, total_sims);
        s = tmp->state;
    }

    return tmp;
}

node_t *_mcts_best_child(node_t *node, uint32_t total_sims) {
    int i, j = 0;
    node_t *c;
    long double max_ucb = -999;

    // evaluate
    for (i = 0; i < BOARD_SIZE; i++) {
        if (node->children[i] == NULL)
            continue;

        c = node->children[i];

        if (c->plays != 0) {
            c->q = ((long double) c->score) / total_sims;
            c->q += sqrtl(2 * log(total_sims) / c->plays);
        } else {
            c->q = MCTS_INITIAL_Q;
        }
    }

    // select
    for (i = 0; i < BOARD_SIZE; i++) {
        if (node->children[i] != NULL) {
            j = i;
            max_ucb = node->children[i]->q;
            break;
        }
    }

    for (i = 0; i < BOARD_SIZE; i++) {
        if (node->children[i] == NULL)
            continue;

        c = node->children[i];
        if (c->q > max_ucb) {
            j = i;
            max_ucb = c->q;
        }
    }

    return node->children[j];
}

node_t *_mcts_expand(node_t *node) {
    int i;
    node_t *new_node = NULL;
    state_t *new_state;

    for (i = 0; i < node->state->available_move_n; i++) {
        new_state = state_advance(node->state, node->state->available_moves[i]);
        tree_init(&new_node, node, (char) node->state->available_moves[i], new_state);
    }

    return new_node;
}

int64_t _mcts_random_playout(node_t *node, char player) {
    char s;
    state_t *tmp = node->state, *prev;

    while ((s = state_status(tmp)) == PE) {
        prev = tmp;
        tmp = state_advance(tmp, random_genmove(tmp));

        if (prev != node->state)
            state_destroy(prev);
    }

    if (s == player || s == PD) {
        return MCTS_POSITIVE_REWARD;
    }

    return -MCTS_NEGATIVE_REWARD * (1 + board_legal_action_count(tmp->board));
}

void _mcts_backpropagate(node_t *node, int64_t result) {
    node_t *tmp = node;

    while (tmp != NULL) {
        tmp->plays++;
        tmp->score += result;
        tmp = tmp->parent;
    }
}
