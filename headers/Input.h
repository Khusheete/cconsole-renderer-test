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