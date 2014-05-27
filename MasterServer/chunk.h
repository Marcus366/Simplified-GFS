#ifndef __CHUNK_H__
#define __CHUNK_H__

#include "gfs.h"

typedef struct chunk_s {
	uint_64 uuid;
	uint_32 chk_addr;
	uint_16 chk_port;
} chunk_t;


#endif