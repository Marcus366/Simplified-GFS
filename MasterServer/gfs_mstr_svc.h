#ifndef __GFS_MSTR_H__
#define __GFS_MSTR_H__

#include "gfs_rpc.h"
#include "gfs_list.h"
#include "gfs_filetree.h"


extern gfs_list_t *chk_svcs;
extern gfs_node_t *filetree_root;

extern int on_clnt_open(const char *path, int oflags, mode_t mode);
extern int on_clnt_close(int fd);
extern ssize_t on_clnt_read(int fd, void *buf, size_t count);
extern ssize_t on_clnt_write(int fd, const void *buf, size_t nbytes);

extern int on_chk_reg(char* arg);
extern int on_chk_unreg(char* arg);


#endif