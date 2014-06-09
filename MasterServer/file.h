#ifndef __FILE_H__
#define __FILE_H__

#include "gfs_chk.h"
#include "gfs_filetree.h"
#include <fcntl.h>


#define FILE_TYPE_FILE 		1
#define FILE_TYPE_FOLDER 	2
#define MAX_FILE_SIZE 		100000


typedef struct file_s {
	char 		name[33]; 	/* with at most 32 byte length name */
	int 		type; 		/* file type */
	struct gfs_list_s 	*chunks; 	/* list of chunks here */

	/* attribute for opening file */
	gfs_chk_t* 	cur_chk;
	int 		oflags;
	mode_t 		mode;
} file_t;


extern file_t *fds[MAX_FILE_SIZE];			
extern int fd_count;

extern void file_new(file_t **file, const char* name, int type);
extern void file_free(file_t **file);

/* create a file and add it to the filetree */
extern file_t *file_create(const char *path, mode_t mode, int type, gfs_node_t* root);

/* return 1 when equal, 0 when not equal. */
extern int file_equal(file_t* ,file_t* );


#endif
