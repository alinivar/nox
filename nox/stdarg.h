
#ifndef __stdarg_h__
#define __stdarg_h__

#ifdef __cplusplus
extern "C" {
#endif

typedef char* va_list;

#define __va_align(x, alignment) \
        ((x + (alignment-1)) & ~(alignment))

#define va_start(v, l) \
        (void)(v = (char*)&l + sizeof(l));

#define va_arg(v, l) \
        *(l*)((v += sizeof(l)) - sizeof(l))

#define va_end(v) \
        ((void)v)

#ifdef __cplusplus
}
#endif

#endif
