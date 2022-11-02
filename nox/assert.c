
#include "assert.h"
#include "stdio.h"
#include "stdlib.h"

void _assert_failed(const char* file, const char* line, const char* expr) {
    fprintf(stderr, "Assertion failed: `%s`, file `%s`, line `%s`\n", expr, file, line);
    exit(EXIT_FAILURE);
}
