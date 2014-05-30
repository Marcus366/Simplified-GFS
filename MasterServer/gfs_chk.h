#ifndef __GFS_CHUNK_H__
#define __GFS_CHUNK_H__


typedef struct gfs_chk_s {
	uint64_t uuid;				/* the unique id of chunk    			*/
	uint32_t chk_addr; 			/* chunk location server address 		*/
	int	 chk_fd; 			/* chunk server fd if opened,  -1 otherwise	*/
} gfs_chk_t;

extern void gfs_chk_new(gfs_chk_t **chk);
extern void gfs_chk_free(gfs_chk_t **chk);


#endif