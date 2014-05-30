#ifndef __FILETREE_H__
#define __FILETREE_H__

#include "file.h"
#include "gfs_list.h"

typedef struct node_s {
	file_t			*file;
	struct node_s	*father;	/* daddy */
	gfs_list_t		*child;		/* data */
} node_t;

extern void create_node(node_t *father, file_t *file);
extern void delete_node(node_t **node);
extern node_t* find_node(node_t *root, file_t *file);
extern void free_node(node_t **node);

#endif
