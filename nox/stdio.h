
#ifndef __stdio_h__
#define __stdio_h__

#ifdef __cplusplus
extern "C" {
#endif

#include "stdarg.h"

#ifndef __file__
#define __file__
typedef struct _FILE FILE;
#endif

#ifndef __size_t__
#define __size_t__
typedef unsigned long long size_t;
#endif

#ifndef __fpos_t__
#define __fpos_t__
typedef long long fpos_t;
#endif

#ifndef BUFSIZ
#define BUFSIZ (512)
#endif

#ifndef EOF
#define EOF (-1)
#endif

#ifndef FILENAME_MAX
#define FILENAME_MAX (260)
#endif

#ifndef FOPEN_MAX
#define FOPEN_MAX (20)
#endif

#ifndef L_tmpnam
#define L_tmpnam (260)
#endif

#ifndef NULL
#define NULL ((void*)0)
#endif

#ifndef TMP_MAX
#define TMP_MAX (0x7fffffff)
#endif

extern FILE* __pIoFiles[3];

#define stdin   (__pIoFiles[0])
#define stdout  (__pIoFiles[1])
#define stderr  (__pIoFiles[2])

enum {
    SEEK_SET,
    SEEK_CUR,
    SEEK_END,
};

/* fopen: Open file */
FILE* fopen(const char* pFileName, const char* pMode);

/* fgetc: Get character from stream */
int fgetc(FILE* pFile);

/* getc: Get character from stream */
int getc(FILE* pFile);

/* fgets: Get string from stream */
char* fgets(char* pString, int len, FILE* pFile);

/* fseek: Reposition stream position indicator */
long fseek(FILE* pFile, long long offset, int origin);

/* ftell: Get current position in stream */
long ftell(FILE* pFile);

/* rewind: Set position of stream to the beginning */
void rewind(FILE* pFile);

/* rename: Rename file */
int rename(const char* pOldName, const char* pNewName);

/* fread: Read block of data from stream */
size_t fread(void* pBuffer, size_t blockSize, size_t blockCount, FILE* pFile);

/* fwrite: Write block of data to stream */
size_t fwrite(const void* pBuffer, size_t blockSize, size_t blockCount, FILE* pFile);

/* fclose: Close file */
void fclose(FILE* pFile);

/* remove: Remove file */
int remove(const char* pFileName);

/* putc: Write character to stream */
int putc(int character, FILE* pFile);

/* putchar: Write character to stdout */
int putchar(int character);

/* puts: Write string to stdout */
int puts(const char* pString);

/* printf: Print formatted data to stdout */
int printf(const char* pFormat, ...);

/* fprintf: Write formatted data to stream */
int fprintf(FILE* pFile, const char* pFormat, ...);

/* vfprintf: Write formatted data from variable argument list to stream */
int vfprintf(FILE* pFile, const char* pFormat, va_list args);

#ifdef __cplusplus
}
#endif

#endif
