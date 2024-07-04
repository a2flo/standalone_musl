#ifndef LIBUCONTEXT_LIBUCONTEXT_H
#define LIBUCONTEXT_LIBUCONTEXT_H

#include <stddef.h>

#if defined(__aarch64__)
#include "aarch64/bits.h"
#elif defined(__x86_64__)
#include "x86_64/bits.h"
#else
#error "unhandled architecture"
#endif

#ifdef __cplusplus
extern "C" {
#endif

int  libucontext_getcontext(libucontext_ucontext_t *);
void libucontext_makecontext(libucontext_ucontext_t *, void (*)(), int, ...);
int  libucontext_setcontext(const libucontext_ucontext_t *);
int  libucontext_swapcontext(libucontext_ucontext_t *, const libucontext_ucontext_t *);

#ifdef __cplusplus
}
#endif

#endif
