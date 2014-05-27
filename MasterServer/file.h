#ifndef __FILE_H__
#define __FILE_H__


typedef struct file_s {
	char name[32]; /* with at most 32 byte length name */
	/* list of chunks here */
} file_t;


extern file_t* get_file_by_path(const char *full_path);


#endif