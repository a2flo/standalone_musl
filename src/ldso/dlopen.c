#include <dlfcn.h>
#include "dynlink.h"

static void *stub_dlopen(const char *file, int mode)
{
	__dl_seterr("Dynamic loading not supported");
	return 0;
}

// we have a proper dlopen
// TODO: support both ldso_rcrt1 and the dynamic loader
//weak_alias(stub_dlopen, dlopen);
