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
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "main.h"
#include "interface/ascii.h"
#include "utils/binarysearch.h"

/**
 * felix_ttt [interface]
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char **argv) {
    interface_t interface;

    if (argc == 2) {
        if (strncmp(argv[1], "ascii", 4) == 0) {
            interface = ascii;
        } else if (strncmp(argv[1], "ttp", 3) == 0) {
            interface = ttp;
        } else if (strncmp(argv[1], "help", 4) == 0) {
            printf("Usage: felix_ttt [interface]\n");
            exit(0);
        } else {
            fprintf(stderr, "Unknown interface: %s\n", argv[1]);
            exit(1);
        }
    } else {
        interface = DEFAULT_INTERFACE;
    }

    // ====

    print_banner();

    // ====

    switch (interface) {
        case ascii:
            ascii_loop();
            break;
        case ttp:
            break;
    }

    return 0;
}

void print_banner() {
    size_t c;
    char buf[32];
    FILE *fp = fopen("banner.txt", "r");
    if (fp == NULL) {
        fprintf(stderr, "can't open banner file: %s", strerror(errno));
        exit(2);
    }

    while ((c = fread(buf, sizeof(char), 32, fp)) > 0) {
        fwrite(buf, sizeof(char), c, stdout);
    }

    fclose(fp);

    // ==

    printf("%6sTic Tac Toe\n", "");
    printf("%5sVersion %s\n\n", "", FELIX_VERSION);

}