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

#ifndef FELIX_TTT_MCTS_H
#define FELIX_TTT_MCTS_H

#include <stdint.h>
#include "tree.h"
#include "../game/state.h"

/**
 * MCTS Time Limit, in milliseconds
 */
#define MCTS_TIME_LIMIT 1
#define MCTS_POSITIVE_REWARD 1
#define MCTS_NEGATIVE_REWARD 1
#define MCTS_INITIAL_Q 10

/**
 *
 * @param state
 * @param player
 * @return
 */
int mcts_genmove(state_t *state, char player);

/**
 *
 * @param root
 * @param player
 * @return
 */
node_t *_mcts_descend(node_t *root, uint32_t total_sims);

/**
 *
 * @param node
 * @param player
 * @return
 */
node_t *_mcts_best_child(node_t *node, uint32_t total_sims);

/**
 *
 * @param node
 * @return
 */
node_t *_mcts_expand(node_t *node);

/**
 *
 * @param node
 * @return
 */
int64_t _mcts_random_playout(node_t *node, char player);

/**
 *
 * @param node
 * @param result
 */
void _mcts_backpropagate(node_t *node, int64_t result);

#endif //FELIX_TTT_MCTS_H
