#ifndef __FILETREE_H__
#define __FILETREE_H__


#include "linklist.h"

struct file_t;

typedef struct node_s {
	file_t 		*file;
	node_s    *father;  /* daddy */
	linklist   *child;	/* data */
} node_t;

extern void create_node(node_t *father, file_t *file);
extern void delete_node(node_t **node);
extern node_t* find_node(node_t *root, file_t *file);
extern node_t* find_node_by_name(node_t *root, char *name);
extern void free_node(node_t **node);
extern file_t* get_file_by_path(node_t *root, const char *full_path);

#endif
         