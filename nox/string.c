
#include "string.h"

void* memcpy(void* dst, const void* src, size_t len) {
    char* d = (char*)dst;
    char* s = (char*)src;

    for (size_t i = 0; i < len; i++)
        *d++ = *s++;

    return dst;
}

void* memmove(void* dst, const void* src, size_t len) {
    char* d = (char*)dst;
    char* s = (char*)src;

    if ((s < d) && (d < s + len)) {
        d += len;
        s += len;
        while (len--) {
            *d-- = *s--;
        }
    }
    else {
        while (len--) {
            *d++ = *s++;
        }
    }

    return dst;
}

char* strcpy(char* dst, const char* src) {
    for (size_t i = 0; src[i]; i++)
        dst[i] = src[i];

    return dst;
}

char* strncpy(char* dst, const char* src, size_t len) {
    for (size_t i = 0; i < len; i++)
        dst[i] = src[i];

    return dst;
}

char* strcat(char* dst, const char* src) {
    size_t dstlen = strlen(dst);

    for (size_t i = 0; src[i]; i++)
        dst[dstlen + i] = src[i];

    return dst;
}

char* strncat(char* dst, const char* src, size_t len) {
    size_t dstlen = strlen(dst);

    for (size_t i = 0; i < len; i++)
        dst[dstlen + i] = src[i];

    return dst;
}

int memcmp(const void* a, const void* b, size_t len) {
    const char* first = (const char*)a;
    const char* second = (const char*)b;

    for (size_t i = 0; i < len; i++) {
        if (*first != *second) {
            return (*first) - (*second);
        }

        first++;
        second++;
    }

    return 0;
}

int strcmp(const char* a, const char* b) {
    size_t i = 0;

    while (a[i] && b[i]) {
        if (a[i] != b[i])
            return a[i] - b[i];

        i += 1;
    }

    return 0;
}

int strcoll(const char* a, const char* b) {
    return strcmp(a, b);
}

int strncmp(const char* a, const char* b, size_t len) {
    size_t i = 0;

    while (a[i] && b[i] && i < len) {
        if (a[i] != b[i])
            return a[i] - b[i];

        i += 1;
    }

    return 0;
}

size_t strxfrm(char* dst, const char* src, size_t len) {
    // NOT IMPLEMENTED
    (void) dst;
    (void) src;
    (void) len;

    return 0;
}

void* memchr(const void* ptr, int value, size_t len) {
    char* p = (char*)ptr;
    unsigned char v = (unsigned char)value;

    for (size_t i = 0; i < len; i++)
        if (p[i] == v)
            return &p[i];

    return NULL;
}

char* strchr(const char* str, int chr) {
    char c = (char)chr;

    for (size_t i = 0; str[i]; i++)
        if (str[i] == c)
            return (char*)&str[i];

    return NULL;
}

size_t strcspn(const char* a, const char* b) {
    size_t i;

    for (i = 0; a[i]; i++)
        for (size_t j = 0; b[j]; j++)
            if (a[i] == b[j])
                return i;

    return i;
}

char* strpbrk(const char* a, const char* b) {
    for (size_t i = 0; a[i]; i++)
        for (size_t j = 0; b[j]; j++)
            if (a[i] == b[j])
                return (char*)&a[i];

    return NULL;
}

char* strrchr(const char* str, int chr) {
    char* last = NULL;

    for (size_t i = 0; str[i]; i++) {
        if (str[i] == chr)
            last = (char*)&str[i];
    }

    return last;
}

size_t strspn(const char* a, const char* b) {
    size_t cnt = 0;

    for (size_t i = 0; a[i]; i++)
        for (size_t j = 0; b[j]; j++)
            if (a[i] == b[j])
                cnt++;

    return cnt;
}

char* strstr(const char* a, const char* b) {
    for (size_t i = 0; a[i]; i++)
        if (strcmp(&a[i], b) == 0)
            return (char*)&a[i];

    return NULL;
}

char* strtok(char* str, const char* delims) {
    char* tok;
    static char* olds;

    if (str == NULL)
        str = olds;

    str += strspn(str, delims);
    if (*str == '\0') {
        olds = str;
        return NULL;
    }

    tok = str;
    str = strpbrk(tok, delims);
    if (str == NULL) {
        olds = memchr(tok, '\0', ~0ull);
    }
    else {
        *str = '\0';
        olds = str + 1;
    }

    return tok;
}

void* memset(void* ptr, int value, size_t len) {
    char* p = (char*)ptr;

    while (len--)
        *p++ = (char)value;

    return ptr;
}

char* strerror(int errnum) {
    // NOT IMPLEMENTED
    (void) (errnum);

    return "NOT IMPLEMENTED";
}

size_t strlen(const char* str) {
    size_t i = 0;
    while (str[i]) i += 1;
    return i;
}
