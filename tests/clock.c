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
#include "Input.h"

#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <time.h>


#define PI 3.141592654


void draw_clock_hand(int x, int y, int r, float angle);
int min(int a, int b);


int main(void) {
    cnsr_init(1000000 / 60);

    int width;
    int height;

    int center_x, center_y;
    int radius;
    
    while (true) {
        const CnsrInput input = cnsr_listen_input(1000000 / 20);

        if (input.type == CNSR_SINT)
            exit(EXIT_SUCCESS);

        if (cnsr_begin_draw()) {
            width = cnsr_get_width();
            height = cnsr_get_height();

            center_x = width / 2;
            center_y = height / 2;

            radius = min(width / 3, height / 3);

            cnsr_clear(black);
        }

        cnsr_fill_color(black);
        cnsr_rect(center_x - radius - 1, center_y - radius - 1, 2 * radius, 2 * radius);

        cnsr_fill_color(green);
        cnsr_ellipse(center_x, center_y, radius * 2, radius * 2);

        cnsr_fill_color(white);
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);

        float sangle = 2. * PI * (float)tm.tm_sec  / 60.0;
        float mangle = 2. * PI * (float)tm.tm_min  / 60.0;
        float hangle = 2. * PI * (float)tm.tm_hour / 24.0;

        draw_clock_hand(center_x, center_y, radius - 1, sangle);
        draw_clock_hand(center_x, center_y, (2 * radius / 3) - 1, mangle);
        draw_clock_hand(center_x, center_y, (radius / 2) - 1, hangle);

        cnsr_end_draw();
    }
    
    return EXIT_SUCCESS;
}


void draw_clock_hand(int x, int y, int r, float angle) {
    angle = angle - PI / 2;
    int px = r * cos(angle);
    int py = r * sin(angle);
    cnsr_line(x, y, x + px, y + py);
}


int min(int a, int b) {
    return (a < b)? a : b;
}