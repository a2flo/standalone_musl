#define _GNU_SOURCE
#include <errno.h>   /* errno */
#include <fcntl.h>   /* O_CLOEXEC, O_RDONLY */
#include <pthread.h> /* pthread_atfork */
#include <sched.h>   /* sched_yield, CPU_ALLOC, CPU_FREE */
#include <unistd.h>  /* open, read */

#include "alias.h" /* weak_alias */

/**
 * Underlying function for pthread_cleanup_push.
 */
void __pthread_register_cancel(void *buf)
{
}

/**
 * Underlying function for pthread_cleanup_push.
 */
void __pthread_unregister_cancel(void *buf)
{
}

/**
 * Register fork handlers.
 *
 * LSB 5.0: LSB-Core-generic/baselib---register-atfork.html
 */
int __register_atfork(void (*prepare)(void), void (*parent)(void),
                      void (*child)(void), void *__dso_handle)
{
	return pthread_atfork(prepare, parent, child);
}
weak_alias(__register_atfork, register_atfork);

/**
 * Yield this thread.
 */
int pthread_yield(void)
{
	return sched_yield();
}

/**
 * Allocate a large enough CPU set
 */
cpu_set_t *__sched_cpualloc(size_t __count)
{
	return CPU_ALLOC(__count);
}

/**
 * Free a CPU set allocated by __sched_cpualloc
 */
void __sched_cpufree(cpu_set_t *__set)
{
	return CPU_FREE(__set);
}

/**
 * Gets the mutex kind (non-portable variant).
 */
int pthread_mutexattr_getkind_np(const pthread_mutexattr_t *attr, int *kind)
{
	return pthread_mutexattr_gettype(attr, kind);
}

/**
 * Sets the mutex kind (non-portable variant).
 */
int pthread_mutexattr_setkind_np(pthread_mutexattr_t *attr, int kind)
{
	if (kind > PTHREAD_MUTEX_ERRORCHECK || kind < PTHREAD_MUTEX_NORMAL)
		return EINVAL;

	return pthread_mutexattr_settype(attr, kind);
}
