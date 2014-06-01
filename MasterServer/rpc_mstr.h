#ifndef __RPC_MSTR_H__
#define __RPC_MSTR_H__

#include "gfs_chk.h"
#include <fcntl.h>
#include <sys/types.h>

extern int ask_chk_open(int chk, const char *name, int oflags, mode_t mode);
extern int ask_chk_close(int chk, int fd);


#endif
