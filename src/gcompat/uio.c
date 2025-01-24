#include <sys/syscall.h>
#include <sys/uio.h>		/* iovec, pwritev, preadv */
#include <errno.h>		/* errno */
#include <unistd.h>		/* syscall */

ssize_t pwritev64v2(int fd, const struct iovec *iov, int count, off_t ofs, int flags)
{
	if (flags != 0) {
		errno = ENOTSUP;
		return -1;
	}

	if (ofs == -1) {
		return writev(fd, iov, count);
	}

	return syscall(__NR_pwritev2, fd, iov, count, ofs);
}

ssize_t preadv64v2(int fd, const struct iovec *iov, int count, off_t ofs, int flags)
{
	if (flags != 0) {
		errno = ENOTSUP;
		return -1;
	}

	if (ofs == -1) {
		return readv(fd, iov, count);
	}

	return syscall(__NR_preadv2, fd, iov, count, ofs);
}
