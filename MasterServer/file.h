#ifndef __FILE_H__
#define __FILE_H__

#include <fcntl.h>
#include "filetree.h"

#define FILE_TYPE_FILE 1
#define FILE_TYPE_FOLDER 2


typedef struct file_s {
	char name[33]; /* with at most 32 byte length name */
	int type; /* file type */
	/* list of chunks here */
} file_t;


extern void file_new(file_t **file, char* name, int type);
extern void file_free(file_t **file);


extern void file_create(const char *path, mode_t mode, int type, node_t* root);
extern int file_equal(file_t* ,file_t* );  /* return 1 when equal, 0 when not equal. */



#endif
