#ifndef __GFS_FILETREE_H__
#define __GFS_FILETREE_H__


#include "gfs_list.h"

extern struct file_s;
typedef struct file_s file_t;


typedef struct gfs_node_s gfs_node_t;
struct gfs_node_s {
	file_t		*file;
	gfs_node_t 	*father;  /* daddy */
	gfs_list_t	*child;	/* data */
};


extern void gfs_create_node(gfs_node_t **node, gfs_node_t *father,file_t *file);
extern void gfs_delete_node(gfs_node_t **node);
extern gfs_node_t* gfs_find_node(gfs_node_t *root, file_t *file);
extern gfs_node_t* gfs_find_node_by_name(gfs_node_t *root, char *name);
extern void gfs_free_node(gfs_node_t **node);
extern file_t* gfs_get_file_by_path(gfs_node_t *root, const char *full_path);
extern gfs_node_t* gfs_get_node_by_path(gfs_node_t *root, const char *full_path);
extern void gfs_filetree_print(gfs_node_t *root);   


#endif
         