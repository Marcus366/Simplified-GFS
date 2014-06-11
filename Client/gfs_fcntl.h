/**
 * The gfs_fcntl.h contains the file operation of GFS, which is uesd the same as POSIX standard IO.
 */

#ifndef __GFS_FCNTL_H__
#define __GFS_FCNTL_H__


#include <fcntl.h>
#include <stddef.h>
#include <sys/types.h>

extern int gfs_init(const char* mstr_ip);

extern int gfs_open(const char *path, int oflags, mode_t mode);

extern int gfs_close(int fd);

extern ssize_t gfs_read(int fd, void *buf, size_t count);

extern ssize_t gfs_write(int fd, const void *buf, size_t nbytes);


#endif
