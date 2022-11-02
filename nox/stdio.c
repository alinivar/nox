
#include "stdio.h"
#include "string.h"

#define WIN32_LEAN_AND_MEAN 1
#include <Windows.h>

#define BIT(x) (1 << x)

typedef enum fopen_flags_t {
    READ    = BIT(0),
    WRITE   = BIT(1),
    APPEND  = BIT(2),
    UPDATE  = BIT(3),
} fopen_flags_t;

struct _FILE {
    HANDLE          Handle;
    size_t          Offset;
    fopen_flags_t   Flags;

    int             IsOpen;
};

static  FILE  __iofiles[3]  = {0};
        FILE* __pIoFiles[3] = { &__iofiles[0],
                                &__iofiles[1],
                                &__iofiles[2],};

static FILE     files[FOPEN_MAX] = {0};
static size_t   filesOpened = 0;

void __init_stdio(void) {
    __iofiles[0].Handle = GetStdHandle(STD_INPUT_HANDLE);
    __iofiles[1].Handle = GetStdHandle(STD_OUTPUT_HANDLE);
    __iofiles[2].Handle = GetStdHandle(STD_ERROR_HANDLE);

    SetConsoleMode(__iofiles[0].Handle, ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT);

    __iofiles[0].Flags = READ | UPDATE;
    __iofiles[1].Flags = WRITE | UPDATE;
    __iofiles[2].Flags = WRITE | UPDATE;

    __iofiles[0].Offset = 0;
    __iofiles[1].Offset = 0;
    __iofiles[2].Offset = 0;
}

FILE* fopen(const char* pFileName, const char* pMode) {
    if (filesOpened >= FOPEN_MAX)
        return NULL;

    FILE* pFile = 0;
    for (size_t i = 0; i < FOPEN_MAX; i++) {
        if (files[i].IsOpen == 0) {
            pFile = &files[i];
            break;
        }
    }

    fopen_flags_t flags = 0;

    while (*pMode) {
        switch (*pMode) {
            case 'r':
                flags |= READ;
                break;
            case 'w':
                flags |= WRITE;
                break;
            case 'a':
                flags |= APPEND;
                break;
            case '+':
                flags |= UPDATE;
                break;
            default:
                break;
        }
        pMode++;
    }

    DWORD desiredAccess = 0;
    if (flags & READ) desiredAccess |= FILE_SHARE_READ;
    if (flags & WRITE) desiredAccess |= FILE_SHARE_WRITE;
    if (flags & APPEND) desiredAccess |= FILE_SHARE_WRITE;
    if (flags & UPDATE) desiredAccess |= (FILE_SHARE_READ | FILE_SHARE_WRITE);

    DWORD creationDisposition = 0;
    if (flags & READ) creationDisposition = OPEN_EXISTING;
    if (flags & WRITE) creationDisposition = OPEN_ALWAYS;
    if (flags & APPEND) creationDisposition = OPEN_ALWAYS;

    pFile->Handle = CreateFileA(pFileName, desiredAccess, 0, 0, creationDisposition, FILE_ATTRIBUTE_NORMAL, NULL);

    if ((flags & WRITE) && (GetLastError() == ERROR_ALREADY_EXISTS)) {
        CloseHandle(pFile->Handle);
        DeleteFileA(pFileName);
        pFile->Handle = CreateFileA(pFileName, desiredAccess, 0, 0, creationDisposition, FILE_ATTRIBUTE_NORMAL, NULL);
    }

    if (pFile->Handle == INVALID_HANDLE_VALUE)
        return NULL;

    if (flags & APPEND)
        GetFileSizeEx(pFile->Handle, (PLARGE_INTEGER)&pFile->Offset);
    else
        pFile->Offset = 0;

    LARGE_INTEGER offset;
    offset.QuadPart = pFile->Offset;
    SetFilePointerEx(pFile->Handle, offset, NULL, FILE_BEGIN);

    pFile->Flags = flags;
    pFile->IsOpen = 1;

    filesOpened += 1;

    return pFile;
}

int fgetc(FILE* pFile) {
    int c;
    fread(&c, 1, 1, pFile->Handle);

    return c;
}

int getc(FILE* pFile) {
    int c;

    DWORD charsRead;
    ReadConsoleA(pFile->Handle, &c, 1, &charsRead, NULL);

    return c;
}

char* fgets(char* pString, int len, FILE* pFile) {
    DWORD charsRead;
    ReadConsoleA(pFile->Handle, pString, len, &charsRead, NULL);

    return pString;
}

long fseek(FILE* pFile, long long offset, int origin) {
    if (pFile->Flags & APPEND)
        return 1;

    DWORD moveMethod = (DWORD)origin; // Maps to Windows API nicely
    
    LARGE_INTEGER largeInt;
    largeInt.QuadPart = offset;

    LARGE_INTEGER newOffset;
    BOOL r = SetFilePointerEx(pFile->Handle, largeInt, &newOffset, moveMethod);

    if (!r)
        return GetLastError();

    pFile->Offset = newOffset.QuadPart;

    return 0;
}

long ftell(FILE* pFile) {
    return (long)pFile->Offset;
}

void rewind(FILE* pFile) {
    fseek(pFile, 0, SEEK_SET);
}

int rename(const char* pOldName, const char* pNewName) {
    if (MoveFileA(pOldName, pNewName))
        return 0;
    else
        return GetLastError();
}

size_t fread(void* pBuffer, size_t blockSize, size_t blockCount, FILE* pFile) {
    if (((pFile->Flags & READ) == 0) &&
        ((pFile->Flags & UPDATE) == 0))
        return 0;

    DWORD bytesRead;
    ReadFile(pFile->Handle, pBuffer, (DWORD)(blockSize * blockCount), &bytesRead, NULL);

    return (size_t)bytesRead;
}

size_t fwrite(const void* pBuffer, size_t blockSize, size_t blockCount, FILE* pFile) {
    if (((pFile->Flags & READ)) &&
        ((pFile->Flags & UPDATE) == 0))
        return 0;

    DWORD bytesWritten;
    WriteFile(pFile->Handle, pBuffer, (DWORD)(blockSize * blockCount), &bytesWritten, NULL);

    pFile->Offset += bytesWritten;

    return (size_t)bytesWritten;
}

void fclose(FILE* pFile) {
    if (!pFile)
        return;

    if (pFile->Handle)
        CloseHandle(pFile->Handle);

    pFile->Handle   = 0;
    pFile->Offset   = 0;
    pFile->Flags    = 0;
    pFile->IsOpen   = 0;

    filesOpened -= (filesOpened > 0) ? 1 : 0;
}

int remove(const char* pFileName) {
    if (DeleteFileA(pFileName))
        return 0;
    else
        return GetLastError();
}

int putc(int character, FILE* pFile) {
    return fwrite(&character, 1, 1, pFile);
}

int putchar(int character) {
    putc(character, stdout);
    return character;
}

int puts(const char* pString) {
    int len = fwrite(pString, strlen(pString), 1, stdout);
    putchar('\n');

    return len;
}

int printf(const char* pFormat, ...) {
    va_list args;
    va_start(args, pFormat);
    int len = vfprintf(stdout, pFormat, args);
    va_end(args);

    return len;
}

int fprintf(FILE* pFile, const char* pFormat, ...) {
    va_list args;
    va_start(args, pFormat);
    int len = vfprintf(pFile, pFormat, args);
    va_end(args);

    return len;
}

/* vfprintf stuff */
#define PRINTF_BUFSIZ 16384

/* Long long to string */
static char* _lltoa(long long value, int base, int uppercase) {
    static char buffer[64];
    int i = 62;

    int sign = value < 0;
    if (sign)
        value = -value;

    for (; i && value; value /= base, i--)
        if (uppercase)
            buffer[i+sign] = "0123456789ABCDEF"[value % base];
        else
            buffer[i+sign] = "0123456789abcdef"[value % base];

    if (sign) {
        buffer[i+1] = '-';
    }

    return &buffer[i+1];
}

/* Int to string */
static char* _itoa(int value, int base, int uppercase) {
    return _lltoa((long long)value, base, uppercase);
}

/* Unsigned long long to string */
static char* _ulltoa(unsigned long long value, int base, int uppercase) {
    static char buffer[64];
    int i = 62;

    for (; i && value; value /= base, i--)
        if (uppercase)
            buffer[i] = "0123456789ABCDEF"[value % base];
        else
            buffer[i] = "0123456789abcdef"[value % base];

    return &buffer[i+1];
}

/* Unsigned int to string */
static char* _utoa(unsigned int value, int base, int uppercase) {
    return _ulltoa((unsigned long long)value, base, uppercase);
}

/* printf in all of it's glory! */

int vfprintf(FILE* pFile, const char* pFormat, va_list args) {
    static char buffer[PRINTF_BUFSIZ];
    size_t bufferSize = 0;

    while (*pFormat) {
        if (*pFormat == '%') {
            pFormat++;

            switch (*pFormat++) {
                // signed int
                case 'd':
                case 'i': {
                    int value = va_arg(args, int);
                    const char* pString = _itoa(value, 10, 0);

                    strcpy(&buffer[bufferSize], pString);
                    bufferSize += strlen(pString);
                } break;

                // unsigned int
                case 'u': {
                    unsigned int value = va_arg(args, unsigned int);
                    const char* pString = _utoa(value, 10, 0);

                    strcpy(&buffer[bufferSize], pString);
                    bufferSize += strlen(pString);
                } break;

                // lowercase float
                case 'f': {

                } break;

                // uppercase float
                case 'F': {
                    
                } break;

                // lowercase unsigned number hexadecimal
                case 'x': {
                    unsigned int value = va_arg(args, unsigned int);
                    const char* pString = _utoa(value, 16, 0);

                    strcpy(&buffer[bufferSize], pString);
                    bufferSize += strlen(pString);
                } break;

                // uppercase unsigned number hexadecimal
                case 'X': {
                    unsigned int value = va_arg(args, unsigned int);
                    const char* pString = _utoa(value, 16, 1);

                    strcpy(&buffer[bufferSize], pString);
                    bufferSize += strlen(pString);
                } break;

                // unsigned int octal
                case 'o': {
                    unsigned int value = va_arg(args, unsigned int);
                    const char* pString = _utoa(value, 8, 0);

                    strcpy(&buffer[bufferSize], pString);
                    bufferSize += strlen(pString);
                } break;

                // null-terminated string
                case 's': {
                    const char* pString = va_arg(args, char*);
                    strcpy(&buffer[bufferSize], pString);

                    bufferSize += strlen(pString);
                } break;

                // character
                case 'c': {
                    buffer[bufferSize++] = va_arg(args, char);
                } break;

                // void* value
                case 'p': {
                    unsigned long long value = va_arg(args, unsigned long long);
                    const char* pString = _ulltoa(value, 16, 0);

                    strcpy(&buffer[bufferSize], pString);
                    bufferSize += strlen(pString);
                } break;

                default: {
                    buffer[bufferSize++] = *pFormat++;
                } break;
            }
        }
        else {
            buffer[bufferSize++] = *pFormat++;
        }
    }

    fwrite(buffer, bufferSize, 1, pFile);

    return (int)bufferSize;
}
