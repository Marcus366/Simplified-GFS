#ifndef __GFS_FILETREE_H__
#define __GFS_FILETREE_H__


#include "gfs_list.h"

struct file_t;

typedef struct gfs_node_s {
	file_t 		*file;
	node_s    *father;  /* daddy */
	linklist   *child;	/* data */
} gfs_node_t;

extern void gfs_create_node(gfs_node_t *father, file_t *file);
extern void gfs_delete_node(gfs_node_t **node);
extern gfs_node_t* gfs_find_node(gfs_node_t *root, file_t *file);
extern gfs_node_t* gfs_find_node_by_name(gfs_node_t *root, char *name);
extern void gfs_free_node(gfs_node_t **node);
extern file_t* gfs_get_file_by_path(gfs_node_t *root, const char *full_path);

#endif
         