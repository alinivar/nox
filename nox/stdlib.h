
#ifndef __stdlib_h__
#define __stdlib_h__

#ifdef __cplusplus
extern "C" {
#endif

/* EXIT_SUCCESS: successful exit code */
#ifndef EXIT_SUCCESS
#define EXIT_SUCCESS 0
#endif

/* EXIT_FAILURE: failed exit code */
#ifndef EXIT_FAILURE
#define EXIT_FAILURE 1
#endif

/* NULL: syntax sugar for 0 */
#ifndef NULL
#define NULL ((void*)0)
#endif

/* abort: Abort current process */
void abort(void);

/* exit: Terminate calling process */
void exit(int code);

/* _Exit: Terminate calling process */
void _Exit(int code);

#ifdef __cplusplus
}
#endif

#endif
