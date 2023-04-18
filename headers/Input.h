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


#ifndef INPUT_H
#define INPUT_H

typedef enum {
    CNSR_NULL,
    // normal char
    CNSR_CHAR,
    // arrow keys
    CNSR_UP,
    CNSR_DOWN,
    CNSR_RIGHT,
    CNSR_LEFT,
    // signal interrupt (cmd-c)
    CNSR_SINT,
    // signal quit (cmd-d)
    CNSR_SQUIT,
    // backspace
    CNSR_BACK,
    // del / suppr
    CNSR_DEL,
    // page-up/down
    CNSR_PUP,
    CNSR_PDOWN,

    CNSR_HOME,
    CNSR_END,
} CnsrInputType;

typedef struct {
    CnsrInputType type;
    char c;
} CnsrInput;


//called by the renderer init
void _cnsr_init_input();

//blocks until the users types some input
CnsrInput cnsr_get_input();

//linstens for input for a given amound of time (in microseconds)
CnsrInput cnsr_listen_input(int timeout);


#endif //#ifndef INPUT_H