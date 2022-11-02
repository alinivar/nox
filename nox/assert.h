
#ifndef __assert_h__
#define __assert_h__

#ifdef __cplusplus
extern "C" {
#endif

#ifdef NDEBUG
    #define assert(expr) ((void)0)
#else
    extern void _assert_failed(const char* file, const char* line, const char* expr);

    #define _STR(x) _VAL(x)
    #define _VAL(x) #x
    #define assert(expr) if (!(expr)) { _assert_failed(__FILE__, _STR(__LINE__), #expr); }
#endif

#define static_assert _Static_assert

#ifdef __cplusplus
}
#endif

#endif
