#include "Input.h"
#include "consts.h"

#include <stdio.h>
#include <sys/select.h>
#include <unistd.h>


CnsrInput cnsr_get_input() {
    CnsrInput r = {CNSR_NULL, '\0'};

    char in = getc(stdin);

    if (in == '\x1b') {
        in = getc(stdin);
        if (in == '[') { //CSI
            in = getc(stdin);
            switch (in) {
                case 'A':
                    r.type = CNSR_UP;
                    break;
                case 'B':
                    r.type = CNSR_DOWN;
                    break;
                case 'C':
                    r.type = CNSR_LEFT;
                    break;
                case 'D':
                    r.type = CNSR_RIGHT;
                    break;
                case '3':
                    if (getc(stdin) == '~') r.type = CNSR_DEL;
                    break;
                case '5':
                    if (getc(stdin) == '~') r.type = CNSR_PUP;
                    break;
                case '6':
                    if (getc(stdin) == '~') r.type = CNSR_PDOWN;
                    break;
                case 'H':
                    r.type = CNSR_HOME;
                    break;
                case 'F':
                    r.type = CNSR_END;
                    break;
            }
        }
    } else if (in == '\x03') { // ctrl-c
        r.type = CNSR_SINT;
    } else if (in == '\x03') { // ctrl-d
        r.type = CNSR_SQUIT;
    } else if (in == '\x7F') { // backspace
        r.type = CNSR_BACK;
    } else {
        r.type = CNSR_CHAR;
        r.c = in;
    }
    return r;
}


CnsrInput cnsr_listen_input(int timeout) {
    static fd_set set;
    FD_ZERO(&set);
    FD_SET(STDIN, &set);

    struct timeval t;
    t.tv_sec = 0;
    t.tv_usec = timeout;

    select(STDIN + 1, &set, NULL, NULL, &t);

    if (FD_ISSET(STDIN, &set)) {
        return cnsr_get_input();
    }

    // if there was nothing to read, return null
    CnsrInput r = {CNSR_NULL, '\0'};
    return r;
}