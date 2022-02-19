#include "Renderer.h"
#include "consts.h"

#include <stdlib.h>
#include <stdio.h>
#include <termios.h>


#define STDIN 0
#define STDOUT 1

static struct termios base_iconfig;
static struct termios iconfig;

// static struct termios base_oconfig;
// static struct termios oconfig;

//console data
static int console_width  = 0;
static int console_height = 0;


/* ----- private functions ----- */
void _cnsr_exit();
void _cnsr_move_cursor(int x, int y);
void _cnsr_update_canvas_size_info();
int _cnsr_read_size();


/* ----- function implementation ----- */
void cnsr_init() {
    FATAL_ERROR(atexit(&_cnsr_exit), "[CNSR] Could not register exit function");

    FATAL_ERROR(tcgetattr(STDIN, &iconfig) < 0, "[CNSR] Could not get config for stdin");
    base_iconfig = iconfig; //save the previous terminal configuration
    iconfig.c_lflag &= !(ICANON | ECHO); //do not echo from stdin and make input available
    //iconfig.c_cc[VMIN] = 0;
    //iconfig.c_cc[VTIME] = 0; // ehhh ?
    FATAL_ERROR(tcsetattr(STDIN, 0, &iconfig) < 0, "[CNSR] Could not set config for stdin");

    // FATAL_ERROR(tcgetattr(STDOUT, &oconfig) < 0, "[CNSR] Could not get config for stdout");
    // base_oconfig = oconfig; //save the previous terminal configuration
    // oconfig.c_lflag &= !ICANON;
    // FATAL_ERROR(tcsetattr(STDOUT, 0, &oconfig) < 0, "[CNSR] Could not set config for stdout");
    printf("\x1b[?25l"); //hide cursor
}


void _cnsr_exit() {
    FATAL_ERROR(tcsetattr(STDIN, 0, &base_iconfig) < 0, "[CNSR] Could not set config for stdin");
    // FATAL_ERROR(tcsetattr(STDOUT, 0, &base_oconfig) < 0, "[CNSR] Could not set config for stdout");
    printf("\x1b[?25h"); //show cursor
    printf("\x1b[m");    //reset formatting
    fflush(stdout);
    system("clear");
}


int cnsr_get_width() {
    return console_width;
}


int cnsr_get_height() {
    return console_height;
}


void _cnsr_move_cursor(int x, int y) {
    printf("\x1b[%i;%iH", y, x);
}


void cnsr_fill_color(const CnsrColor color) {
    printf("\x1b[48;2;%i;%i;%im", color.r, color.g, color.b);
}


void cnsr_text_color(const CnsrColor color) {
    printf("\x1b[38;2;%i;%i;%im", color.r, color.g, color.b);
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
    console_width = atoi(buff);

    index = 0;
    c = ' ';
    while (c != 'R' && c != EOF && index < SIZE) {
        c = getc(stdin);
        buff[index++] = c;
    }
    if (index == SIZE || c == EOF) return 0;

    buff[index] = '\0';
    console_height = atoi(buff);

    return 1;
}


void _cnsr_update_canvas_size_info() {
    _cnsr_move_cursor(1000, 1000);
    printf("\x1b[6n");
    fflush(stdout);
    do {
        while (getc(stdin) != '[');
    } while (!_cnsr_read_size());
    //scanf("%i;%iR", &console_width, &console_height)
}


void cnsr_begin_draw() {
    _cnsr_update_canvas_size_info();
}


void cnsr_end_draw() {
    fflush(stdout);
}


void cnsr_point_of_char(const char c, int x, int y) {
    _cnsr_move_cursor(x, y);
    printf("%c", c);
}


void cnsr_point(int x, int y) {
    cnsr_point_of_char(' ', x, y);
}


void cnsr_line_of_char(const char c, int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1);
    int sx = (x1 < x2)? 1 : -1;
    int dy = -abs(y2 - y1);
    int sy = (y1 < y2)? 1 : -1;

    int err = dx + dy;
    
    cnsr_point_of_char(c, x1, y1);
    while ((x1 != x2 || y1 != y2)
        && ((x1 <= console_width  && sx > 0) || (x1 > 0 && sx < 0))
        && ((y1 <= console_height && sy > 0) || (y1 > 0 && sy < 0)))
    {
        int e2 = 2 * err;
        if (e2 >= dy) {
            err += dy;
            x1 += sx;
        }
        if (e2 >= dx) {
            err += dx;
            y1 += sy;
        }
        cnsr_point_of_char(c, x1, y1);
    }
}


void cnsr_line(const int x1, int y1, int x2, int y2) {
    cnsr_line_of_char(' ', x1, y1, x2, y2);
}


void cnsr_text(const char* str, int x, int y) {
    _cnsr_move_cursor(x, y);
    printf("%s", str);
}


void cnsr_rect_boundary_of_chars(const char c, int x, int y, int w, int h) {
    cnsr_line_of_char(c, x        , y        , x + w - 1, y        );
    cnsr_line_of_char(c, x + w - 1, y        , x + w - 1, y + h - 1);
    cnsr_line_of_char(c, x + w - 1, y + h - 1, x        , y + h - 1);
    cnsr_line_of_char(c, x        , y + h - 1, x        , y        );
}


void cnsr_rect_boundary(int x, int y, int w, int h) {
    cnsr_rect_of_chars(' ', x, y, w, h);
}


void cnsr_rect_of_chars(const char c, int x, int y, int w, int h) {
    if (x <= 0) {
        x = 1;
        w += x - 1;
    }
    if (y <= 0) {
        y = 1;
        h += y - 1;
    }

    int dx = (w >= 0)? 1 : -1;
    int dy = (h >= 0)? 1 : -1;

    for (int j = 0; abs(j) < abs(h); j += dy) {
        if (y + j > console_height) break;
        _cnsr_move_cursor(x, y + j);
        for (int i = 0; abs(i) < abs(w); i += dx) {
            if (x + i > console_width) break;
            printf("%c", c);
        }
    }
}


void cnsr_rect(int x, int y, int w, int h) {
    cnsr_rect_of_chars(' ', x, y, w, h);
}


//mid-point ellipse algorithm: https://www.cpp.edu/~raheja/CS445/MEA.pdf
void _cnsr_plot_ellipse_points(const char c, int cx, int cy, int x, int y) {
    cnsr_point_of_char(c, cx + x, cy + y);
    cnsr_point_of_char(c, cx + x, cy - y);
    cnsr_point_of_char(c, cx - x, cy - y);
    cnsr_point_of_char(c, cx - x, cy + y);
}

void cnsr_ellipse_of_char(const char c, int cx, int cy, int w, int h) {
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
    _cnsr_plot_ellipse_points(c, cx, cy, x, y);
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
        _cnsr_plot_ellipse_points(c, cx, cy, x, y);
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
        _cnsr_plot_ellipse_points(c, cx, cy, x, y);
    }
}


void cnsr_ellipse(int cx, int cy, int w, int h) {
    cnsr_ellipse_of_char(' ', cx, cy, w, h);
}


void cnsr_clear() {
    fflush(stdout);
    system("clear");
}