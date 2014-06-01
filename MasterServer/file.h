#ifndef __FILE_H__
#define __FILE_H__

#include <fcntl.h>
#include "gfs_filetree.h"

#define FILE_TYPE_FILE 1
#define FILE_TYPE_FOLDER 2
#define MAX_FILE_SIZE 100000


typedef struct file_s {
	char name[33]; /* with at most 32 byte length name */
	int type; /* file type */
	/* list of chunks here */
} file_t;


extern int fds[MAX_FILE_SIZE];			
extern int fd_count;

extern void file_new(file_t **file, char* name, int type);
extern void file_free(file_t **file);


extern void file_create(const char *path, mode_t mode, int type, gfs_node_t* root);   /* create a file and add it to the filetree */
extern int file_equal(file_t* ,file_t* );  /* return 1 when equal, 0 when not equal. */
extern int get_fd(file_t* file);		/* return fd, and also put the fd in the fds array. */
extern int binary_search_fd(int fd);    /* binary search for fd in fds in case of conflict */


#endif
