#ifndef __GFS_CHUNK_H__
#define __GFS_CHUNK_H__

#include <stdint.h>
#include "gfs_list.h"


typedef struct gfs_chk_s {
	uint64_t uuid;				/* the unique id of chunk    			*/
	uint32_t chk_addr; 			/* chunk location server address 		*/
	int	 chk_fd; 			/* chunk server fd if opened,  -1 otherwise	*/
} gfs_chk_t;

typedef struct gfs_chksvc_s
{
	char ip[5];   /* ip address */
	uint32_t chk_size;     /* the count of stored chunk */
	gfs_list_t *chks;
} gfs_chksvc_t;

extern void gfs_chk_new(gfs_chk_t **chk);
extern void gfs_chk_free(gfs_chk_t **chk);

extern void gfs_chksvc_new(gfs_chksvc_t **chksvc);
extern void gfs_chksvc_free(gfs_chksvc_t **chksvc);


#endif