
#include "assert.h"
#include "stdio.h"
#include "string.h"

int main(int ArgCount, char* Args[]) {
    (void) ArgCount;
    (void) Args;

    printf("Hello, world!\n");

    assert(0);

    return(0);
}
