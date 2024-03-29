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

// #include "Image.h"
// #include "consts.h"

// #include <stdlib.h>


// /* ===== private functions ===== */
// inline void _cnsr_check_out_of_bound(CnsrImage img, int x, int y);


// /* ===== function implementation ===== */

// inline void _cnsr_check_out_of_bound(CnsrImage img, int x, int y) {
//     FATAL_ERROR(x >= img.width || y >= img.height, 
//                 "[CNSR] Image index out of bound (%i, %i) in image of size (%i, %i)", x, y, img.width, img.height);
// }


// CnsrImage cnsr_alloc_image(int w, int h) {
//     CnsrImage result = {calloc(w * h, sizeof(CnsrColor)), w, h};
//     FATAL_ERROR(result.pix_color == NULL, 
//                 "[CNSR] Could not allocate %lu bits of memory for the image.", w * h * sizeof(CnsrColor));
//     return result;
// }


// void cnsr_free_image(CnsrImage img) {
//     free(img.pix_color);
// }


// CnsrColor cnsr_get_pixel(CnsrImage img, int x, int y) {
//     _cnsr_check_out_of_bound(img, x, y);
//     int index = x + y * img.width;
//     return img.pix_color[index];
// }


// void cnsr_set_pixel(CnsrImage img, int x, int y, CnsrColor col) {
//     _cnsr_check_out_of_bound(img, x, y);
//     int index = x + y * img.width;
//     img.pix_color[index] = col;
// }