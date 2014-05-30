/**
 * This file contains file operation.
 * It is the same as POSIX standard.
 */

#ifndef __GFS_FCNTL_H__
#define __GFS_FCNTL_H__

extern int gfs_open(const char *path, int oflags, mode_t mode);

extern int gfs_close(int fd);

extern ssize_t gfs_read(int fd, void *buf, size_t count);

extern ssize_t gfs_write(int fd, const void *buf, size_t nbytes);


#endif
