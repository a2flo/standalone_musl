/*
 * struct mallinfo pulled from mallinfo.3:
 *
 * Copyright (c) 2012 by Michael Kerrisk <mtk.manpages@gmail.com>
 *
 * Permission is granted to make and distribute verbatim copies of this
 * manual provided the copyright notice and this permission notice are
 * preserved on all copies.
 *
 * Permission is granted to copy and distribute modified versions of this
 * manual under the conditions for verbatim copying, provided that the
 * entire resulting derived work is distributed under the terms of a
 * permission notice identical to this one.
 *
 * Since the Linux kernel and libraries are constantly changing, this
 * manual page may be incorrect or out-of-date.  The author(s) assume no
 * responsibility for errors or omissions, or for damages resulting from
 * the use of the information contained herein.  The author(s) may not
 * have taken the same level of care in the production of this manual,
 * which is licensed free of charge, as they might when working
 * professionally.
 *
 * Formatted or processed versions of this manual, if unaccompanied by
 * the source, must acknowledge the copyright and authors of this work.
 */

#include <malloc.h> /* memalign */
#include <stdlib.h> /* {m,c,re}alloc, free */
#include <string.h> /* memset */
#include <unistd.h> /* sbrk */

#include "alias.h" /* alias */

struct mallinfo {
	int arena;    /* Non-mmapped space allocated (bytes) */
	int ordblks;  /* Number of free chunks */
	int smblks;   /* Number of free fastbin blocks */
	int hblks;    /* Number of mmapped regions */
	int hblkhd;   /* Space allocated in mmapped regions (bytes) */
	int usmblks;  /* Maximum total allocated space (bytes) */
	int fsmblks;  /* Space in freed fastbin blocks (bytes) */
	int uordblks; /* Total allocated space (bytes) */
	int fordblks; /* Total free space (bytes) */
	int keepcost; /* Top-most, releasable space (bytes) */
};
struct mallinfo2 {
	size_t arena;    /* Non-mmapped space allocated (bytes) */
	size_t ordblks;  /* Number of free chunks */
	size_t smblks;   /* Number of free fastbin blocks */
	size_t hblks;    /* Number of mmapped regions */
	size_t hblkhd;   /* Space allocated in mmapped regions (bytes) */
	size_t usmblks;  /* Maximum total allocated space (bytes) */
	size_t fsmblks;  /* Space in freed fastbin blocks (bytes) */
	size_t uordblks; /* Total allocated space (bytes) */
	size_t fordblks; /* Total free space (bytes) */
	size_t keepcost; /* Top-most, releasable space (bytes) */
};

void *__libc_memalign(size_t align, size_t len)
{
	void *result = NULL;
	if (posix_memalign(&result, align, len) != 0)
		return NULL;
	return result;
}
alias(__libc_memalign, __memalign);

void *__sbrk(intptr_t increment)
{
	return sbrk(increment);
}

struct mallinfo mallinfo(void)
{
	struct mallinfo info;
	memset(&info, 0, sizeof(info));
	return info;
}

struct mallinfo2 mallinfo2(void)
{
	struct mallinfo2 info;
	memset(&info, 0, sizeof(info));
	return info;
}

int malloc_trim(size_t pad)
{
	/* This concept doesn't really map to musl's malloc */
	return 0;
}

void mtrace(void)
{
	/* Not implemented on purpose. */
	return;
}

void muntrace(void)
{
	/* Not implemented on purpose. */
	return;
}

// dummy malloc hooks
void *(*volatile __malloc_hook)(size_t size, const void *caller) = NULL;
void *(*volatile __realloc_hook)(void *ptr, size_t size, const void *caller) = NULL;
void *(*volatile __memalign_hook)(size_t alignment, size_t size, const void *caller) = NULL;
void (*volatile __free_hook)(void *ptr, const void *caller) = NULL;
void (*__malloc_initialize_hook)(void) = NULL;
void (*volatile __after_morecore_hook)(void) = NULL;
