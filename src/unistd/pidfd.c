#include <syscall.h>
#include <signal.h>
#include <stdlib.h>

int pidfd_getfd(int pidfd, int targetfd, unsigned int flags) {
	return syscall(SYS_pidfd_getfd, pidfd, targetfd, flags);
}

int pidfd_open(pid_t pid, unsigned int flags) {
	return syscall(SYS_pidfd_open, pid, flags);
}

int pidfd_send_signal(int pidfd, int sig, siginfo_t *info, unsigned int flags) {
	return syscall(SYS_pidfd_send_signal, pidfd, sig, info, flags);
}

// for glibc compat
pid_t pidfd_getpid(int fd) {
	abort_with_reason("pidfd_getpid unimplemented");
}
int pidfd_spawn(int *pidfd, const char *path, const void *fa, const void *attrp,
				char *const argv[], char *const envp[]) {
	abort_with_reason("pidfd_spawn unimplemented");
}
int pidfd_spawnp(int *pidfd, const char *path, const void *fa, const void *attrp,
				 char *const argv[], char *const envp[]) {
	abort_with_reason("pidfd_spawnp unimplemented");
}
