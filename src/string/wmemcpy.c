#include <wchar.h>
#include <assert.h>

wchar_t *wmemcpy(wchar_t *restrict d, const wchar_t *restrict s, size_t n)
{
	wchar_t *a = d;
	while (n--) *d++ = *s++;
	return a;
}

wchar_t *__wmemcpy_chk(wchar_t *restrict d, const wchar_t *restrict s, size_t n, size_t ns1) {
	assert(ns1 >= n);
	return wmemcpy(d, s, n);
}
