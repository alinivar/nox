
#ifndef __string_h__
#define __string_h__

#ifdef __cplusplus
extern "C" {
#endif

/* size_t: largest unsigned integer type */
#ifndef __size_t__
#define __size_t__
typedef unsigned long long size_t;
#endif

/* NULL: syntax sugar for 0 */
#ifndef NULL
#define NULL ((void*)0)
#endif

/* memcpy: Copy blocks of memory */
void* memcpy(void* dst, const void* src, size_t len);

/* memmove: Move blocks of memory */
void* memmove(void* dst, const void* src, size_t len);

/* strcpy: Copy string */
char* strcpy(char* dst, const char* src);

/* strncpy: Copy characters from string */
char* strncpy(char* dst, const char* src, size_t len);

/* strcat: Concatenate strings */
char* strcat(char* dst, const char* src);

/* strncat: Append characters from string */
char* strncat(char* dst, const char* src, size_t len);

/* memcmp: Compare two blocks of memory */
int memcmp(const void* a, const void* b, size_t len);

/* strcmp: Compare two strings */
int strcmp(const char* a, const char* b);

/* strcoll: Compare two strings using locale */
int strcoll(const char* a, const char* b);

/* strncmp: Compare characters of two strings */
int strncmp(const char* a, const char* b, size_t len);

/* strxfrm: Transform string using locale */
size_t strxfrm(char* dst, const char* src, size_t len);

/* memchr: Locate character in block of memory */
void* memchr(const void* ptr, int value, size_t len);

/* strchr: Locate first occurrence of character in string */
char* strchr(const char* str, int chr);

/* strcspn: Get span until character in string */
size_t strcspn(const char* a, const char* b);

/* strpbrk: Locate characters in string */
char* strpbrk(const char* a, const char* b);

/* strrchr: Locate last occurrence of character in string */
char* strrchr(const char* str, int chr);

/* strspn: Get span of character set in string */
size_t strspn(const char* a, const char* b);

/* strstr: Locate substring */
char* strstr(const char* a, const char* b);

/* strtok: Split string into tokens */
char* strtok(char* str, const char* delims);

/* memset: Fill block of memory */
void* memset(void* ptr, int value, size_t len);

/* strerror: Get pointer to error message string */
char* strerror(int errnum);

/* strlen: Get string length */
size_t strlen(const char* str);

#ifdef __cplusplus
}
#endif

#endif
