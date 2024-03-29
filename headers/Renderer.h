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


#ifndef RENDERER_H
#define RENDERER_H


// TODO: exit signal (ctrl+c ctrl+d)

#include <stdbool.h>


typedef struct {
    unsigned char r, g, b;
} CnsrColor;


static const CnsrColor black          = {0  , 0  , 0  };
static const CnsrColor white          = {229, 229, 229};
static const CnsrColor red            = {229, 0  , 0  };
static const CnsrColor green          = {0  , 205, 0  };
static const CnsrColor yellow         = {205, 205, 0  };
static const CnsrColor blue           = {0  , 0  , 238};
static const CnsrColor magenta        = {205, 0  , 205};
static const CnsrColor cyan           = {0  , 205, 205};
static const CnsrColor gray           = {127, 127, 127};
static const CnsrColor bright_white   = {255, 255, 255};
static const CnsrColor bright_red     = {255, 0  , 0  };
static const CnsrColor bright_green   = {0  , 255, 0  };
static const CnsrColor bright_yellow  = {255, 255, 0  };
static const CnsrColor bright_blue    = {0  , 0  , 255};
static const CnsrColor bright_magenta = {255, 0  , 255};
static const CnsrColor bright_cyan    = {0  , 255, 255};


//initialisation functions
void cnsr_init();

/* should be used at the begining of a draw loop 
   returns weather the screen was resized        */
bool cnsr_begin_draw();
/* finally draws on the screen (if it did not push the buffer to the screen yet) */
void cnsr_end_draw();


//information getter functions
int cnsr_get_width();
int cnsr_get_height();


//simple draw functions
void cnsr_clear(const CnsrColor color);

void cnsr_fill_color(const CnsrColor color);
// void cnsr_text_color(const CnsrColor color);

// void cnsr_point_of_char(const char c, int x, int y);
void cnsr_point(int x, int y);
// void cnsr_line_of_char(const char c, int x1, int y1, int x2, int y2);
void cnsr_line(int x1, int y1, int x2, int y2);


// void cnsr_rect_boundary_of_chars(const char c, int x, int y, int w, int h);
void cnsr_rect_boundary(int x, int y, int w, int h);
// void cnsr_rect_of_chars(const char c, int x, int y, int w, int h);
void cnsr_rect(int x, int y, int w, int h);


// void cnsr_ellipse_of_char(const char c, int cx, int cy, int w, int h);
void cnsr_ellipse(int cx, int cy, int w, int h);


// void cnsr_text(const char* str, int x, int y);


#endif //#ifndef RENDERER_H
