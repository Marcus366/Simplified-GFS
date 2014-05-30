#ifndef __GFS_MSTR_H__
#define __GFS_MSTR_H__

#include "gfs_rpc.h"


extern CLIENT *cl;


extern int on_clnt_open(const char *path, int oflags, mode_t mode);
extern int on_clnt_close(int fd);
extern ssize_t on_clnt_read(int fd, void *buf, size_t count);
extern ssize_t on_clnt_write(int fd, const void *buf, size_t nbytes);


#endif