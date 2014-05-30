#ifndef __FILETREE_H__
#define __FILETREE_H__


#include "gfs_list.h"


extern struct file_s;
typedef struct file_s file_t;


typedef struct node_s {
	file_t			*file;
	struct node_s	*father;	/* daddy */
	gfs_list_t		*child;		/* data */
} node_t;

extern void create_node(node_t *father, file_t *file);      /*   create a node */
extern void delete_node(node_t **node);						/* you are not blind so I won't tell you what is this function for*/
extern node_t* find_node(node_t *root, file_t *file);		/* find a node by the root of tree and the file(search from the children of the root) */
extern node_t* find_node_by_name(node_t *root, char *name);   
extern void free_node(node_t **node);
extern file_t* get_file_by_path(node_t *root, const char *full_path);

#endif
