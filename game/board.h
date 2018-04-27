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

#ifndef FELIX_TTT_BOARD_H
#define FELIX_TTT_BOARD_H

/**
 *
 */
#define BOARD_SIZE 9

/**
 * Player X
 */
#define P1 'X'

/**
 * Player O
 */
#define P2 'O'

/**
 * Empty Cell
 */
#define PE '.'

/**
 * Result of Draw
 */
#define PD 'D'

/**
 *
 * @param board
 */
void board_init(char **board);

/**
 *
 * @param board
 */
void board_destroy(char *board);

/**
 *
 * @param board
 * @return
 */
int board_legal_action_count(char *board);

/**
 *
 * @param board board to extract legal actions from
 * @param actions address of action array to be filled in
 * @param action_n address of number of actions to be filled in
 */
void board_legal_actions(char *board, int **actions, int *action_n);

/**
 *
 * @param board
 * @param action
 * @return new board
 */
char *board_advance(char *board, int action, char player);

#endif //FELIX_TTT_BOARD_H
