#include <stdlib.h>
#include <sys/mount.h>
#include "syscall.h"

int mount(const char *special, const char *dir, const char *fstype, unsigned long flags, const void *data)
{
	return syscall(SYS_mount, special, dir, fstype, flags, data);
}

int umount(const char *special)
{
	return syscall(SYS_umount2, special, 0);
}

int umount2(const char *special, int flags)
{
	return syscall(SYS_umount2, special, flags);
}

#if !defined(SYS_open_tree)
#define SYS_open_tree __NR_open_tree
#endif

int open_tree(int dirfd, const char *path, unsigned int flags)
{
	return syscall(SYS_open_tree, dirfd, path, flags);
}

#if !defined(SYS_fsmount)
#define SYS_fsmount __NR_fsmount
#endif

int fsmount(int fsfd, unsigned int flags, unsigned int attr_flags)
{
	return syscall(SYS_fsmount, fsfd, flags, attr_flags);
}

#if !defined(SYS_fsopen)
#define SYS_fsopen __NR_fsopen
#endif

int fsopen(const char *fsname, unsigned int flags)
{
	return syscall(SYS_fsopen, fsname, flags);
}

#if !defined(SYS_mount_setattr)
#define SYS_mount_setattr __NR_mount_setattr
#endif

int mount_setattr(int dirfd, const char *path, unsigned int flags, struct mount_attr *attr, size_t size)
{
	return syscall(SYS_mount_setattr, dirfd, path, flags, attr, size);
}

#if !defined(SYS_fsconfig)
#define SYS_fsconfig __NR_fsconfig
#endif

int fsconfig(int fd, unsigned int cmd, const char *key, const void *value, int aux)
{
	return syscall(SYS_fsconfig, fd, cmd, key, value, aux);
}

#if !defined(SYS_move_mount)
#define SYS_move_mount __NR_move_mount
#endif

int move_mount(int from_dirfd, const char *from_path, int to_dirfd, const char *to_path, unsigned int flags)
{
	return syscall(SYS_move_mount, from_dirfd, from_path, to_dirfd, to_path, flags);
}

#if !defined(SYS_fspick)
#define SYS_fspick __NR_fspick
#endif

int fspick(int dirfd, const char *path, unsigned int flags)
{
	return syscall(SYS_fspick, dirfd, path, flags);
}
