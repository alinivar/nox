
#include "stdio.h"
#include "stdlib.h"

extern int main(int argc, char* pArgv[]);

extern void __init_stdio(void);

void __init(void) {
    __init_stdio();

    // No argc and argv for now...
    exit(main(0, 0));
}
