#define START "_start"
#define _dlstart_c _start_c
#include "../ldso/dlstart.c"

int main();
weak void _init();
weak void _fini();
int __libc_start_main(int (*)(), int, char **,
	void (*)(), void(*)(), void(*)());

// compared to rcrt1.c, __dls2 became __dls4, because this is now the 4th load stage,
// i.e. we use all prior load stages including the __dls2 from ldso itself
void __dls4(size_t *sp)
{
	__libc_start_main(main, *sp, (void *)(sp+1), _init, _fini, 0);
}
