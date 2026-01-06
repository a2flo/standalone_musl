#include "stdio_impl.h"
#include "intscan.h"
#include "shgetc.h"
#include <inttypes.h>
#include <limits.h>
#include <ctype.h>

static unsigned long long strtox(const char *s, char **p, int base, unsigned long long lim)
{
	FILE f;
	sh_fromstring(&f, s);
	shlim(&f, 0);
	unsigned long long y = __intscan(&f, base, 1, lim);
	if (p) {
		size_t cnt = shcnt(&f);
		*p = (char *)s + cnt;
	}
	return y;
}

unsigned long long strtoull(const char *restrict s, char **restrict p, int base)
{
	return strtox(s, p, base, ULLONG_MAX);
}

long long strtoll(const char *restrict s, char **restrict p, int base)
{
	return strtox(s, p, base, LLONG_MIN);
}

unsigned long strtoul(const char *restrict s, char **restrict p, int base)
{
	return strtox(s, p, base, ULONG_MAX);
}

long strtol(const char *restrict s, char **restrict p, int base)
{
	return strtox(s, p, base, 0UL+LONG_MIN);
}

intmax_t strtoimax(const char *restrict s, char **restrict p, int base)
{
	return strtoll(s, p, base);
}

uintmax_t strtoumax(const char *restrict s, char **restrict p, int base)
{
	return strtoull(s, p, base);
}

unsigned long long __isoc23_strtoull_l(const char *restrict s, char **restrict p, int base, locale_t)
{
	return strtoull(s, p, base);
}

long long __isoc23_strtoll_l(const char *restrict s, char **restrict p, int base, locale_t)
{
	return strtoll(s, p, base);
}

unsigned long __isoc23_strtoul_l(const char *restrict s, char **restrict p, int base, locale_t)
{
	return strtoul(s, p, base);
}

long __isoc23_strtol_l(const char *restrict s, char **restrict p, int base, locale_t)
{
	return strtol(s, p, base);
}

weak_alias(strtol, __strtol_internal);
weak_alias(strtol, __isoc23_strtol);
weak_alias(strtoul, __strtoul_internal);
weak_alias(strtoul, __isoc23_strtoul);
weak_alias(strtoll, __strtoll_internal);
weak_alias(strtoll, __isoc23_strtoll);
weak_alias(strtoull, __strtoull_internal);
weak_alias(strtoull, __isoc23_strtoull);
weak_alias(strtoimax, __strtoimax_internal);
weak_alias(strtoumax, __strtoumax_internal);
weak_alias(strtoimax, __isoc23_strtoimax);
weak_alias(strtoumax, __isoc23_strtoumax);
