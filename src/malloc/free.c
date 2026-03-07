#include <stdlib.h>

void free(void *p)
{
	__libc_free(p);
}

void free_sized(void *p, size_t /* size */)
{
	__libc_free(p);
}

void free_aligned_sized(void *p, size_t /* alignment */, size_t /* size */)
{
	__libc_free(p);
}
