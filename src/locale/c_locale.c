#include "locale_impl.h"
#include <stdint.h>

static const uint32_t empty_mo[] = { 0x950412de, 0, -1, -1, -1 };

const struct __locale_map __c_dot_utf8 = {
	.map = empty_mo,
	.map_size = sizeof empty_mo,
	.name = "C.UTF-8"
};

const struct __locale_struct __c_locale = {
	.cat = 0,
	.__glibc_ctype_b = __ctype_b_table + 128, // == __ctype_b_ptable
	.__glibc_ctype_tolower = NULL,
	.__glibc_ctype_toupper = NULL,
};
const struct __locale_struct __c_dot_utf8_locale = {
	.cat[LC_CTYPE] = &__c_dot_utf8,
	.__glibc_ctype_b = __ctype_b_table + 128, // == __ctype_b_ptable
	.__glibc_ctype_tolower = NULL,
	.__glibc_ctype_toupper = NULL,
};
