
#ifndef __windows_h__
#define __windows_h__

#ifndef NULL
#define NULL ((void*)0)
#endif

typedef char BYTE;

typedef unsigned long ULONG;
typedef ULONG* ULONG_PTR;

typedef long LONG;

typedef unsigned int UINT;

typedef int DWORD;
typedef DWORD* LPDWORD;

typedef long long LONGLONG;

typedef int BOOL;
typedef int WINBOOL;

typedef void* HANDLE;

typedef const char* LPCSTR;

typedef void* PVOID;
typedef const void* LPVOID;

#define WINAPI __stdcall

#define ERROR_ALREADY_EXISTS 183
#define INVALID_HANDLE_VALUE (HANDLE)(6)
DWORD WINAPI GetLastError();

void WINAPI ExitProcess(UINT);

void WINAPI CloseHandle(HANDLE);

#define STD_INPUT_HANDLE ((DWORD)-10)
#define STD_OUTPUT_HANDLE ((DWORD)-11)
#define STD_ERROR_HANDLE ((DWORD)-12)
HANDLE WINAPI GetStdHandle(DWORD);

#define ENABLE_ECHO_INPUT 0x0004
#define ENABLE_LINE_INPUT 0x0002
BOOL WINAPI SetConsoleMode(HANDLE, DWORD);

typedef struct _SECURITY_ATTRIBUTES {
    DWORD nLength;
    LPVOID lpSecurityDescriptor;
    WINBOOL bInheritHandle;
  } SECURITY_ATTRIBUTES, *PSECURITY_ATTRIBUTES, *LPSECURITY_ATTRIBUTES;

#define FILE_SHARE_READ 1
#define FILE_SHARE_WRITE 2

#define OPEN_EXISTING 3
#define OPEN_ALWAYS 4

#define FILE_ATTRIBUTE_NORMAL 0x80

HANDLE WINAPI CreateFileA(LPCSTR, DWORD, DWORD, LPSECURITY_ATTRIBUTES, DWORD, DWORD, HANDLE);
BOOL WINAPI DeleteFileA(LPCSTR);

typedef union _LARGE_INTEGER {
    struct {
      DWORD LowPart;
      LONG HighPart;
    } DUMMYSTRUCTNAME;
    struct {
      DWORD LowPart;
      LONG HighPart;
    } u;
    LONGLONG QuadPart;
  } LARGE_INTEGER;

  typedef LARGE_INTEGER *PLARGE_INTEGER;

BOOL WINAPI GetFileSizeEx(HANDLE, PLARGE_INTEGER);

#define FILE_BEGIN 0
#define FILE_CURRENT 1
#define FILE_END 2
BOOL WINAPI SetFilePointerEx(HANDLE, LARGE_INTEGER, PLARGE_INTEGER, DWORD);

BOOL WINAPI ReadConsoleA(HANDLE, LPVOID, DWORD, LPDWORD, LPVOID);

BOOL WINAPI MoveFileA(LPCSTR, LPCSTR);

typedef struct _OVERLAPPED {
    ULONG_PTR Internal;
    ULONG_PTR InternalHigh;
    union {
        struct {
            DWORD Offset;
            DWORD OffsetHigh;
        } DUMMYSTRUCTNAME;
        PVOID Pointer;
    } DUMMYUNIONNAME;
    HANDLE hEvent;
  } OVERLAPPED, *LPOVERLAPPED;

BOOL WINAPI ReadFile(HANDLE, LPVOID, DWORD, LPDWORD, LPOVERLAPPED);

BOOL WINAPI WriteFile(HANDLE, LPVOID, DWORD, LPDWORD, LPOVERLAPPED);

#endif
