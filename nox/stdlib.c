
#include <Windows.h>
#include "stdlib.h"

void abort(void) {
    ExitProcess(EXIT_FAILURE);
}

void exit(int code) {
    ExitProcess(code);
}

void _Exit(int code) {
    exit(code);
}
