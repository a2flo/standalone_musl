#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <stddef.h>
#include <fcntl.h>
#include <unistd.h>

int scandir_impl(DIR *d, struct dirent ***res,
	int (*sel)(const struct dirent *),
	int (*cmp)(const struct dirent **, const struct dirent **))
{
	struct dirent *de, **names=0, **tmp;
	size_t cnt=0, len=0;
	int old_errno = errno;

	if (!d) return -1;

	while ((errno=0), (de = readdir(d))) {
		if (sel && !sel(de)) continue;
		if (cnt >= len) {
			len = 2*len+1;
			if (len > SIZE_MAX/sizeof *names) break;
			tmp = realloc(names, len * sizeof *names);
			if (!tmp) break;
			names = tmp;
		}
		names[cnt] = malloc(de->d_reclen);
		if (!names[cnt]) break;
		memcpy(names[cnt++], de, de->d_reclen);
	}

	closedir(d);

	if (errno) {
		if (names) while (cnt-->0) free(names[cnt]);
		free(names);
		return -1;
	}
	errno = old_errno;

	if (cmp) qsort(names, cnt, sizeof *names, (int (*)(const void *, const void *))cmp);
	*res = names;
	return cnt;
}

int scandir(const char *path, struct dirent ***res,
	int (*sel)(const struct dirent *),
	int (*cmp)(const struct dirent **, const struct dirent **))
{
	DIR *d = opendir(path);
	return scandir_impl(d, res, sel, cmp);
}

int scandirat(int dirfd, const char *path, struct dirent ***res,
	int (*sel)(const struct dirent *),
	int (*cmp)(const struct dirent **, const struct dirent **))
{
	if (!path)
	{
		errno = ENOTDIR;
		return -1;
	}

	if (path[0] == '/' || dirfd == AT_FDCWD)
	{
		return scandir(path, res, sel, cmp);
	}

	// NOTE/TODO: probably not fully correct (especially errno handling), but good enough?
	int dfd = openat(dirfd, path, O_RDONLY|O_DIRECTORY|O_CLOEXEC);
	if (dfd == -1)
	{
		errno = ENOTDIR;
		return -1;
	}
	DIR *d = fdopendir(dfd);
	if (!d)
	{
		close(dfd);
		errno = ENOTDIR;
		return -1;
	}
	return scandir_impl(d, res, sel, cmp);
}

weak_alias(scandirat, scandirat64);
