#ifndef __GFS_MSTR_H__
#define __GFS_MSTR_H__

#include "gfs_rpc.h"
#include "gfs_list.h"


/* A list of ip which is the active chunk server ip */
extern gfs_list_t *chk_svcs;


/* A list of CLIENT for master to connect the chunk server */
extern gfs_list_t *chk_clnts;


extern int on_clnt_open(const char *path, int oflags, mode_t mode);
extern int on_clnt_close(int fd);
extern ssize_t on_clnt_read(int fd, void *buf, size_t count);
extern ssize_t on_clnt_write(int fd, const void *buf, size_t nbytes);

extern int on_chk_reg(char* ip);
extern int on_chk_unreg(char* ip);

#endif
