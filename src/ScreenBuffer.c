#include "ScreenBuffer.h"

#include "consts.h"

#include <stdlib.h>
#include <string.h>


/* ===== private functions ===== */
void _cnsr_check_out_of_bound(CnsrScreenBuffer* buff, int x, int y);
void _cnsr_check_cindex_out_of_bound(CnsrScreenBuffer* buff, int index);
int _cnsr_get_chunk_count(int w, int h, int cw, int ch);


/* ===== function implementation ===== */

void _cnsr_check_out_of_bound(CnsrScreenBuffer* sbuff, int x, int y) {
    FATAL_ERROR(x >= sbuff->width || y >= sbuff->height, 
                "[CNSR] Screen buffer index out of bound (%i, %i) in image of size (%i, %i)", 
                x, y, sbuff->width, sbuff->height);
}


void _cnsr_check_cindex_out_of_bound(CnsrScreenBuffer* sbuff, int index) {
    FATAL_ERROR(index >= sbuff->chunk_count, "[CNSR] Chunk index out of bound %i / %i", index, sbuff->chunk_count);
}


int _cnsr_get_chunk_count(int w, int h, int cw, int ch) {
    return ((w + cw - 1) / cw) * ((h + ch - 1) / ch);
}


int cnsr_get_horizontal_chunk_count(CnsrScreenBuffer* sbuff) {
    return (sbuff->width + sbuff->chunk_width - 1) / sbuff->chunk_width;
}


int cnsr_get_vertical_chunk_count(CnsrScreenBuffer* sbuff) {
    return (sbuff->height + sbuff->chunk_height - 1) / sbuff->chunk_height;
}


int cnsr_get_chunk_count(CnsrScreenBuffer* sbuff) {
    return sbuff->chunk_count;
}


void cnsr_get_chunk_coord(CnsrScreenBuffer* sbuff, int index, int* ret_x, int* ret_y) {
    *ret_x = index % cnsr_get_horizontal_chunk_count(sbuff);
    *ret_y = index / cnsr_get_horizontal_chunk_count(sbuff);
}


int cnsr_get_chunk_index(CnsrScreenBuffer* sbuff, int cx, int cy) {
    int horiz_chunk = cnsr_get_horizontal_chunk_count(sbuff);
    return cx + cy * horiz_chunk;
}


int cnsr_get_chunk_of_point(CnsrScreenBuffer* sbuff, int x, int y) {
    int chunk_x = x / sbuff->chunk_width;
    int chunk_y = y / sbuff->chunk_height;
    return cnsr_get_chunk_index(sbuff, chunk_x, chunk_y);
}


CnsrScreenBuffer cnsr_create_screen_buffer(int w, int h, int cw, int ch) {
    //ceil division
    int chunk_count = _cnsr_get_chunk_count(w, h, cw, ch);
    CnsrScreenBuffer result = {
        calloc(w * h, sizeof(CnsrColor)),
        malloc(chunk_count * sizeof(bool)),
        cw,
        ch,
        w,
        h,
        chunk_count
    };
    memset(result.modified, 1, chunk_count * sizeof(bool));
    FATAL_ERROR(result.pix_color == NULL, 
                "[CNSR] Could not allocate %lu bits of memory for the screen buffer.", 
                w * h * sizeof(CnsrColor));
    FATAL_ERROR(result.modified == NULL, 
                "[CNSR] Could not allocate %lu bits of memory for the screen buffer.", 
                chunk_count * sizeof(bool));
    return result;
}


void cnsr_free_screen_buffer(CnsrScreenBuffer* sbuff) {
    free(sbuff->pix_color);
    free(sbuff->modified);
}


bool cnsr_is_modified(CnsrScreenBuffer* sbuff, int index) {
    _cnsr_check_cindex_out_of_bound(sbuff, index);
    return sbuff->modified[index];
}


void cnsr_updated(CnsrScreenBuffer *sbuff, int index) {
    _cnsr_check_cindex_out_of_bound(sbuff, index);
    sbuff->modified[index] = false;
}


void cnsr_set_pixel(CnsrScreenBuffer* sbuff, int x, int y, CnsrColor color) {
    //update pixel
    _cnsr_check_out_of_bound(sbuff, x, y);
    int index = x + y * sbuff->width;
    sbuff->pix_color[index] = color;

    //update chunk
    int chunk_index = cnsr_get_chunk_of_point(sbuff, x, y);
    sbuff->modified[chunk_index] = true;
}


CnsrColor cnsr_get_pixel(CnsrScreenBuffer* sbuff, int x, int y) {
    _cnsr_check_out_of_bound(sbuff, x, y);
    int index = x + y * sbuff->width;
    return sbuff->pix_color[index];
}


void cnsr_resize_screen_buffer(CnsrScreenBuffer* sbuff, int w, int h) {
    int chunk_count = (1 + ((w - 1) / sbuff->chunk_width)) * (1 + ((h - 1) / sbuff->chunk_height));
    sbuff->pix_color = realloc(sbuff->pix_color, w * h * sizeof(CnsrColor));
    sbuff->modified = realloc(sbuff->modified, chunk_count * sizeof(bool));
    sbuff->width = w;
    sbuff->height = h;
    sbuff->chunk_count = _cnsr_get_chunk_count(w, h, sbuff->chunk_width, sbuff->chunk_height);
}


int cnsr_get_real_chunk_width(CnsrScreenBuffer* sbuff, int cx) {
    int hchunk = cnsr_get_horizontal_chunk_count(sbuff);

    if (cx < hchunk - 1) {
        return sbuff->chunk_width;
    } else {
        return sbuff->width % sbuff->chunk_width;
    }
}


int cnsr_get_real_chunk_height(CnsrScreenBuffer* sbuff, int cy) {
    int vchunk = cnsr_get_vertical_chunk_count(sbuff);

    if (cy < vchunk - 1) {
        return sbuff->chunk_height;
    } else {
        return sbuff->height % sbuff->chunk_height;
    }
}