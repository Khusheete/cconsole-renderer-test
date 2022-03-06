#include "Renderer.h"
#include "ScreenBuffer.h"
#include "consts.h"

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <termios.h>
#include <signal.h>
#include <sys/select.h>


static struct termios base_iconfig;
static struct termios iconfig;

//console data
static int console_width  = 0;
static int console_height = 0;

static CnsrColor fill_color;

//screen buffer
static CnsrScreenBuffer sbuff;


/* ----- private functions ----- */
void _cnsr_exit();
void _cnsr_move_cursor(int x, int y);
void _cnsr_update_canvas_size_info();
int _cnsr_read_size();
void _cnsr_set_back_color(const CnsrColor color);
void _cnsr_set_front_color(const CnsrColor color);


/* ----- function implementation ----- */
void cnsr_init() {
    system("clear");

    FATAL_ERROR(atexit(&_cnsr_exit), "[CNSR] Could not register exit function");

    FATAL_ERROR(tcgetattr(STDIN, &iconfig) < 0, "[CNSR] Could not get config for stdin");
    base_iconfig = iconfig; //save the previous terminal configuration
    // do not echo from stdin and make input available
    // and do not interpret signals
    iconfig.c_lflag &= ~(ICANON | ECHO | ISIG); 
    iconfig.c_cc[VMIN] = 1;
    iconfig.c_cc[VTIME] = 0;
    FATAL_ERROR(tcsetattr(STDIN, 0, &iconfig) < 0, "[CNSR] Could not set config for stdin");

    //set default color
    fill_color = white;

    //chunk height should ALWAYS be a multiple of 2
    sbuff = cnsr_create_screen_buffer(1, 1, 16, 16);
    printf("\x1b[?25l"); //hide cursor
}


void _cnsr_exit() {
    FATAL_ERROR(tcsetattr(STDIN, 0, &base_iconfig) < 0, "[CNSR] Could not set config for stdin");
    printf("\x1b[?25h"); //show cursor
    printf("\x1b[m");    //reset formatting
    fflush(stdout);
    system("clear");
    cnsr_free_screen_buffer(&sbuff);
}


int cnsr_get_width() {
    return console_width;
}


int cnsr_get_height() {
    return console_height;
}


void _cnsr_move_cursor(int x, int y) {
    printf("\x1b[%i;%iH", y + 1, x + 1);
}


void _cnsr_set_back_color(const CnsrColor color) {
    printf("\x1b[48;2;%i;%i;%im", color.r, color.g, color.b);
}


void _cnsr_set_front_color(const CnsrColor color) {
    printf("\x1b[38;2;%i;%i;%im", color.r, color.g, color.b);
}


void cnsr_fill_color(const CnsrColor color) {
    fill_color = color;
}


int _cnsr_read_size() {
    static const int SIZE = 6;
    char buff[SIZE];

    int index = 0;
    char c = ' ';
    while (c != ';' && c != EOF && index < SIZE) {
        c = getc(stdin);
        buff[index++] = c;
    }
    if (index == SIZE || c == EOF) return 0;

    buff[index] = '\0';
    console_height = atoi(buff) * 2;

    index = 0;
    c = ' ';
    while (c != 'R' && c != EOF && index < SIZE) {
        c = getc(stdin);
        buff[index++] = c;
    }
    if (index == SIZE || c == EOF) return 0;

    buff[index] = '\0';
    console_width = atoi(buff);
    //buff contains the number of chars and there are twice as many pixels

    return 1;
}


void _cnsr_update_canvas_size_info() {
    do {
        _cnsr_move_cursor(1000, 1000);
        printf("\x1b[6n");
        fflush(stdout);
        while (getc(stdin) != '[');
    } while (!_cnsr_read_size());
}


bool cnsr_begin_draw() {
    int prev_width = console_width;
    int prev_height = console_height;
    _cnsr_update_canvas_size_info();

    if (prev_width != console_width || prev_height != console_height) {
        cnsr_resize_screen_buffer(&sbuff, console_width, console_height);
        return true;
    } else { return false; }
}


void cnsr_end_draw() {
    for (int i = 0; i < cnsr_get_chunk_count(&sbuff); i++) {
        if (cnsr_is_modified(&sbuff, i)) {
            int cx, cy; //in chunk space
            cnsr_get_chunk_coord(&sbuff, i, &cx, &cy);
            
            int width = cnsr_get_real_chunk_width(&sbuff, cx);
            int height = cnsr_get_real_chunk_height(&sbuff, cy);

            cx *= sbuff.chunk_width; //in pixel space
            cy *= sbuff.chunk_height;

            for (int py = 0; py < height; py += 2) {
                _cnsr_move_cursor(cx, (cy + py) / 2); //this is why the chunk height should be a multiple of 2
                for (int px = 0; px < width; px++) {
                    CnsrColor c0 = cnsr_get_pixel(&sbuff, cx + px, cy + py);
                    CnsrColor c1 = cnsr_get_pixel(&sbuff, cx + px, cy + py + 1);
                    // TODO: optimize for common color
                    // u2580 for upper
                    // u2584 for lower
                    _cnsr_set_back_color(c0);
                    _cnsr_set_front_color(c1);
                    printf("▄"); 
                }
            }

            cnsr_updated(&sbuff, i);
        }
    }
    fflush(stdout);
}


void cnsr_point(int x, int y) {
    //cnsr_point_of_char(' ', x, y);
    cnsr_set_pixel(&sbuff, x, y, fill_color);
}


void cnsr_line(int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1);
    int sx = (x1 < x2)? 1 : -1;
    int dy = -abs(y2 - y1);
    int sy = (y1 < y2)? 1 : -1;

    int err = dx + dy;

    cnsr_point(x1, y1);

    while ((x1 != x2 || y1 != y2)
         && ((x1 < console_width  && sx > 0) || (x1 >= 0 && sx < 0))
         && ((y1 < console_height && sy > 0) || (y1 >= 0 && sy < 0)))
     {
        int e2 = 2 * err;
        if (e2 >= dy) {
            err += dy;
            x1 += sx;
        }
        if (e2 <= dx) {
            err += dx;
            y1 += sy;
        }
        cnsr_point(x1, y1);
    }
}


void cnsr_rect_boundary(int x, int y, int w, int h) {
    cnsr_line(x        , y        , x + w - 1, y        );
    cnsr_line(x + w - 1, y        , x + w - 1, y + h - 1);
    cnsr_line(x + w - 1, y + h - 1, x        , y + h - 1);
    cnsr_line(x        , y + h - 1, x        , y        );
}


void cnsr_rect(int x, int y, int w, int h) {
    if (x < 0) {
        x = 1;
        w += x - 1;
    }
    if (y < 0) {
        y = 1;
        h += y - 1;
    }

    int dx = (w > 0)? 1 : -1;
    int dy = (h > 0)? 1 : -1;

    for (int j = 0; abs(j) < abs(h); j += dy) {
        if (y + j >= console_height) break;
        for (int i = 0; abs(i) < abs(w); i += dx) {
            if (x + i >= console_width) break;
            cnsr_point(x + i, y + j);
        }
    }
}


//mid-point ellipse algorithm: https://www.cpp.edu/~raheja/CS445/MEA.pdf
void _cnsr_plot_ellipse_points(int cx, int cy, int x, int y) {
    cnsr_point(cx + x, cy + y);
    cnsr_point(cx + x, cy - y);
    cnsr_point(cx - x, cy - y);
    cnsr_point(cx - x, cy + y);
}


void cnsr_ellipse(int cx, int cy, int w, int h) {
    int a = w / 2;
    int b = h / 2;

    //prepare to plot in the first region
    int x     = 0;
    int y     = b;
    int p     = b * b + (a * a * (1 - 4*b) - 2) / 4;
    int dpe   = 3 * b * b;
    int dpse  = dpe - 2 * a * a * (b - 1);
    int d2pe  = 2 * b * b;
    int d2pse = d2pe + 2 * a * a;

    //plot in the first region
    _cnsr_plot_ellipse_points(cx, cy, x, y);
    while (dpse < 2 * a * a + 3 * b * b) {
        if (p < 0) { //east
            p    += dpe;
            dpe  += d2pe;
            dpse += d2pe;
        } else {     //south-east
            p    += dpse;
            dpe  += d2pe;
            dpse += d2pse;
            y--;
        }
        x += 1;
        _cnsr_plot_ellipse_points(cx, cy, x, y);
    }

    //prepare to plot in the second region
    p   -= (a * a * (4 * y - 3) + b * b * (4 * x + 3) + 2) / 4;
    dpse = 2 * b * b + 3 * a * a;
    int dps  = a * a * (3 - 2 * y);
    int d2ps = 2 * a * a;

    //plot in the second region
    while (y > 0) {
        if (p > 0) { //south
            p    += dps;
            dpe  += d2ps;
            dpse += d2ps;
        } else {     //south-east
            p    += dpse;
            dpe  += d2ps;
            dpse += d2pse;
            x++;
        }
        y--;
        _cnsr_plot_ellipse_points(cx, cy, x, y);
    }
}


void cnsr_clear(const CnsrColor color) {
    for (int i = 0; i < sbuff.width; i++) {
        for (int j = 0; j < sbuff.height; j++) {
            cnsr_set_pixel(&sbuff, i, j, color);
        }
    }
}