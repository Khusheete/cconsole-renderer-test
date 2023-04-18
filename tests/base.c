/*
Copyright 2023 Souchet Ferdinand

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
documentation files (the “Software”), to deal in the Software without restriction, including without limitation the
rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit
persons to whom the Software is furnished to do so.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/


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