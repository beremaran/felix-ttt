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
#include <errno.h>
#include <string.h>
#include "tgf.h"

char *tgf_action_to_cell(int move) {
    static char *x_names = "ABCDEFGHI";
    static char *y_names = "123456789";

    char *a = (char *) malloc(sizeof(char) * 3);
    sprintf(a, "%c%c", x_names[move % 3], y_names[move / 3]);
    return a;
}

void tgf_dump_history(history_t *root, char *file) {
    FILE *fp = fopen(file, "w");
    if (fp == NULL) {
        fprintf(stderr, "can not open file %s: %s\n", file, strerror(errno));
        exit(3);
    }

    // write version
    fprintf(fp, "FF[%d]%c", TGF_VERSION, TGF_SEPARATOR);
    // write we are playing "Classic Tic Tac Toe"
    fprintf(fp, "GM[%d]%c", classic, TGF_SEPARATOR);
    // write we are playing on a 3x3 board
    fprintf(fp, "SZ[3]%c", TGF_SEPARATOR);

    // dump all history
    while (root != NULL) {
        if (root->move == -1)
            break;

        char *cell = tgf_action_to_cell(root->move);
        fprintf(fp, "%c[%s]%c", root->state->turn, cell, TGF_SEPARATOR);
        root = root->next;
        free(cell);
    }

    fclose(fp);
}