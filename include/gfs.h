#ifndef __GFS_H__
#define __GFS_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <fcntl.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#define MASTER_PORT 	3389
#define LISTEN_BACKLOG	14

#define CHUNK_SIZE		1024


#endif
