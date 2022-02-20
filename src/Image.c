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