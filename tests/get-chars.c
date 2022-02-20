#include "Renderer.h"

#include <stdlib.h>!
#include <stdio.h>


int main(void) {
    cnsr_init();

    while (1) {
        char c = getc(stdin);

        if (c == '\3') exit(EXIT_SUCCESS);
        printf("%x - %c\n", c, c);
        fflush(stdout);
    }

    return EXIT_SUCCESS;
}