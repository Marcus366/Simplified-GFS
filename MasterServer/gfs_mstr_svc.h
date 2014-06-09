#ifndef __GFS_MSTR_H__
#define __GFS_MSTR_H__

#include "gfs_rpc.h"
#include "gfs_list.h"
#include "gfs_filetree.h"


/* A list of ip which is the active chunk server ip */
extern gfs_list_t *chk_svcs;
extern gfs_node_t *filetree_root;


extern int on_clnt_open(const char *path, int oflags, mode_t mode);
extern int on_clnt_close(int fd);
extern void on_clnt_read(int fd, chk_info *info);
extern void on_clnt_write(int fd, chk_info *info);

extern void on_clnt_newchk(int fd, chk_info *info);
extern void on_clnt_nextchk(int fd, chk_info *info);


extern int on_chk_reg(char* ip);
extern int on_chk_unreg(char* ip);


#endif
