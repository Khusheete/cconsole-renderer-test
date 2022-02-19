#include "Renderer.h"

#include <stdlib.h>
#include <unistd.h>


int main(void) {
    cnsr_init();

    cnsr_begin_draw();

    cnsr_fill_color(black);
    cnsr_clear();

    cnsr_fill_color(white);
    cnsr_rect(10, 5, 10, 20);

    cnsr_end_draw();
    
    sleep(3);
    return EXIT_SUCCESS;
}