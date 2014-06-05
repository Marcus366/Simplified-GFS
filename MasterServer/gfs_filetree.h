#ifndef __GFS_FILETREE_H__
#define __GFS_FILETREE_H__


#include "gfs_list.h"


typedef struct gfs_node_s gfs_node_t;
struct gfs_node_s {
	struct file_s		*file;
	gfs_node_t 	*father;  /* daddy */
	gfs_list_t	*child;	/* data */
};


extern void gfs_create_node(gfs_node_t **node, gfs_node_t *father, struct file_s *file);
extern void gfs_delete_node(gfs_node_t **node);
extern gfs_node_t* gfs_find_node(gfs_node_t *root, struct file_s *file);
extern gfs_node_t* gfs_find_node_by_name(gfs_node_t *root, char *name);
extern void gfs_free_node(gfs_node_t **node);
extern struct file_s* gfs_get_file_by_path(gfs_node_t *root, const char *full_path);
extern gfs_node_t* gfs_get_node_by_path(gfs_node_t *root, const char *full_path);
extern void gfs_filetree_print(gfs_node_t *root);   


#endif
         