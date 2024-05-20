#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#if defined(__powerpc__)

/* On PowerPC as well as ppc64, we need to fix up __libc_start_main as the
 * glibc and musl versions have wildly different signatures, which would
 * result in the arguments to __libc_start_main being completely wrong.
 *
 * Using dlsym in this context is mildly questionable as this is before
 * the full initialization has been done, but there is no better way.
 */

#include <dlfcn.h>

struct startup_info {
	void *sda_base;
	void *f_main;
	void *f_init;
	void *f_fini;
};

typedef int (*start_main_t)(void *mf, int argc, char **argv);

/*
 * ref: https://git.musl-libc.org/cgit/musl/tree/crt/crt1.c?id=90251cf
 * ref: https://git.musl-libc.org/cgit/musl/tree/src/env/__libc_start_main.c?id=90251cf#n71
 * ref: https://github.com/bminor/glibc/blob/5cb226d/sysdeps/unix/sysv/linux/powerpc/libc-start.c#L36
 */
int __libc_start_main(void *argc, void *argv, void *ev, void *auxv, void *fini,
                      struct startup_info *si, long *p)
{
	(void)argc;
	(void)argv;
	(void)ev;
	(void)auxv;
	(void)fini;
	/* argc/argv from the stack, main from startup_info */
	start_main_t mainf = (start_main_t)dlsym(RTLD_NEXT, "__libc_start_main");
	return mainf(si->f_main, *p, (void *)(p + 1));
}

#endif /* defined(__powerpc__) */

void GCOMPAT__panic(const char *fmt, ...)
{
	va_list va;

	fprintf(stderr, "*** gcompat panic ***\n");

	va_start(va, fmt);
	vfprintf(stderr, fmt, va);
	va_end(va);

	abort();
}
