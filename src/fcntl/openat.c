#include <fcntl.h>
#include <stdarg.h>
#include <stddef.h>
#include "syscall.h"

int openat(int fd, const char *filename, int flags, ...)
{
	mode_t mode = 0;

	if ((flags & O_CREAT) || (flags & O_TMPFILE) == O_TMPFILE) {
		va_list ap;
		va_start(ap, flags);
		mode = va_arg(ap, mode_t);
		va_end(ap);
	}

	return syscall_cp(SYS_openat, fd, filename, flags|O_LARGEFILE, mode);
}

struct open_how;
int openat2(int dirfd, const char *pathname, struct open_how *how, size_t size)
{
	return syscall_cp(SYS_openat2, dirfd, pathname, how, size);
}

weak_alias(openat2, __openat_2);
weak_alias(openat2, openat64_2);
weak_alias(openat2, __openat64_2);
