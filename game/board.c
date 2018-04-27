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
#include "board.h"

void board_init(char **board) {
    int i = 0;
    *board = (char *) malloc(sizeof(char) * BOARD_SIZE);
    bzero(*board, BOARD_SIZE);
    for (; i < BOARD_SIZE; i++)
        (*board)[i] = PE;
}

void board_destroy(char *board) {
    free(board);
}

int board_legal_action_count(char *board) {
    int i, c = 0;
    for (i = 0; i < BOARD_SIZE; i++) {
        if (board[i] == PE) c++;
    }

    return c;
}

void board_legal_actions(char *board, int **actions, int *action_n) {
    int i, j = 0;

    if (*actions != NULL) {
        free(*actions);
    }

    *action_n = board_legal_action_count(board);
    *actions = (int *) malloc(sizeof(int) * *action_n);

    for (i = 0; i < BOARD_SIZE; i++) {
        if (board[i] == PE) {
            (*actions)[j++] = i;
        }
    }
}

char *board_advance(char *board, int action, char player) {
    char *new_board;

    board_init(&new_board);
    new_board[action] = player;

    return new_board;
}