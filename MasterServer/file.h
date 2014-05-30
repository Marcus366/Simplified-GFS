#ifndef __FILE_H__
#define __FILE_H__

#define FILE_TYPE_FILE 1
#define FILE_TYPE_FOLDER 2


typedef struct file_s {
	char name[32]; /* with at most 32 byte length name */
	int type; /* file type */
	/* list of chunks here */
} file_t;


extern file_t* get_file_by_path(const char *full_path);
extern int file_equal(file_t*, file_t* );  /* return 1 when equal, 0 when not equal. */
extern void file_free(file_t **file);


#endif
