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
#include <string.h>
#include "state.h"

void state_init(state_t **state) {
    *state = (state_t *) malloc(sizeof(state_t));

    (*state)->turn = P1;
    board_init(&(*state)->board);

    (*state)->available_moves = NULL;
    board_legal_actions((*state)->board, &(*state)->available_moves, &(*state)->available_move_n);
}

void state_destroy(state_t *state) {
    board_destroy(state->board);
    free(state->available_moves);
    free(state);
}

void state_init_from(state_t *s1, state_t **s2) {
    *s2 = (state_t *) malloc(sizeof(state_t));

    (*s2)->turn = s1->turn;
    board_init(&(*s2)->board);
    memcpy((*s2)->board, s1->board, BOARD_SIZE);

    (*s2)->available_move_n = s1->available_move_n;
    (*s2)->available_moves = (int *) malloc(sizeof(int) * s1->available_move_n);
    memcpy((*s2)->available_moves, s1->available_moves, (*s2)->available_move_n);
}

char state_next_player(state_t *state) {
    return _next_player(state->turn);
}

char _next_player(char player) {
    switch (player) {
        case P1:
            return P2;
        case P2:
            return P1;
        default:
            return PE;
    }
}

state_t *state_advance(state_t *state, int action) {
    state_t *new_state;

    state_init_from(state, &new_state);
    new_state->board[action] = new_state->turn;
    new_state->turn = state_next_player(new_state);

    // recalculate legal actions
    board_legal_actions(new_state->board, &(new_state->available_moves), &(new_state->available_move_n));
    return new_state;
}

char state_status(state_t *state) {
    static const char ENDPOS[8][3] = {
            // horizontal
            {0, 1, 2},
            {3, 4, 5},
            {6, 7, 8},
            // vertical
            {0, 3, 6},
            {1, 4, 7},
            {2, 5, 8},
            // diagonal
            {0, 4, 8},
            {2, 4, 6}
    };

    // ==

    int i, j, f;
    char *b = state->board;

    for (i = 0; i < 8; i++) {
        if (ENDPOS[i][0] == PE || ENDPOS[i][1] == PE || ENDPOS[i][2] == PE)
            continue;

        f = 1;
        for (j = 0; j < 2; j++) {
            f = f && (b[ENDPOS[i][j]] == b[ENDPOS[i][j + 1]]);
        }

        if (f)
            return b[ENDPOS[i][0]];
    }

    if (state->available_move_n == 0)
        return PD;

    return PE;
}