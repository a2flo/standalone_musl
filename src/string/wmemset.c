#include <wchar.h>
#include <assert.h>

wchar_t *wmemset(wchar_t *d, wchar_t c, size_t n)
{
	wchar_t *ret = d;
	while (n--) *d++ = c;
	return ret;
}

wchar_t *__wmemset_chk(wchar_t *d, wchar_t c, size_t n, size_t dstlen) {
	assert(dstlen >= n);
	return wmemset(d, c, n);
}
