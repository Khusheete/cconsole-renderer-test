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


#ifndef SCREEN_BUFFER_H
#define SCREEN_BUFFER_H

#include "Renderer.h"

#include <stdbool.h>


// TODO: use sizeof(variable) or alignof(variable)
// TODO: use background for second pixel (so that both pixels have different colors)
// TODO: have a consistant api (c++ ?)


typedef struct {
    CnsrColor* pix_color;
    bool* modified;
    int chunk_width;
    int chunk_height;
    int width;
    int height;
    int chunk_count;
} CnsrScreenBuffer;


CnsrScreenBuffer cnsr_create_screen_buffer(int w, int h, int cw, int ch);
void cnsr_resize_screen_buffer(CnsrScreenBuffer* sbuff, int w, int h);
void cnsr_free_screen_buffer(CnsrScreenBuffer* sbuff);

int cnsr_get_chunk_count(CnsrScreenBuffer* sbuff);
void cnsr_get_chunk_coord(CnsrScreenBuffer* sbuff, int index, int* ret_x, int* ret_y);
bool cnsr_is_modified(CnsrScreenBuffer* sbuff, int index);
void cnsr_updated(CnsrScreenBuffer* sbuff, int index);

int cnsr_get_horizontal_chunk_count(CnsrScreenBuffer* sbuff);
int cnsr_get_vertical_chunk_count(CnsrScreenBuffer* sbuff);

void cnsr_set_pixel(CnsrScreenBuffer* sbuff, int x, int y, CnsrColor color);
CnsrColor cnsr_get_pixel(CnsrScreenBuffer* sbuff, int x, int y);

int cnsr_get_chunk_index(CnsrScreenBuffer* sbuff, int cx, int cy);
int cnsr_get_chunk_of_point(CnsrScreenBuffer* sbuff, int x, int y);

int cnsr_get_real_chunk_width(CnsrScreenBuffer* sbuff, int cx);
int cnsr_get_real_chunk_height(CnsrScreenBuffer* sbuff, int cy);

#endif //#ifndef SCREEN_BUFFER_H