#include "Renderer.h"

#include <stdlib.h>
#include <unistd.h>


int main(void) {
    cnsr_init();

    cnsr_begin_draw();

    cnsr_clear(black);


    cnsr_fill_color(white);
    cnsr_line(10, 5, 15, 20);

    cnsr_fill_color(red);
    cnsr_rect_boundary(17, 25, 9, 15);

    cnsr_fill_color(yellow);
    cnsr_rect(18, 26, 7, 13);

    cnsr_fill_color(blue);
    cnsr_ellipse(50, 12, 13, 13);

    cnsr_end_draw();
    
    sleep(3);
    return EXIT_SUCCESS;
}