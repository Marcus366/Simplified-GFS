#ifndef	__GFS_LIST_H__
#define	__GFS_LIST_H__


#include <stdint.h>


typedef struct listnode_s {
	struct listnode_s   *next;
	void		   *elem;
} listnode_t;


typedef struct gfs_list_s gfs_list_t;
struct gfs_list_s {
	listnode_t	*head;
	uint16_t 	  size;
};


/* It means that listnode_free_func
 * is a function return void and 
 * receive a void** as argument.
 * This serve as argument of gfs_list_free
 */
typedef  void (*listnode_free_func)(void **);


#define gfs_list_push_back(__list, __elem) \
	(gfs_list_insert(__list, __elem, __list->size))


#define gfs_list_push_front(__list, __elem) \
	(gfs_list_insert(__list, __elem, 0))


/**
 * Following is a function for iterate list.
 * You can use it such like:
 * ----------------------------------------------------
 * void* pvoid;
 * gfs_list_froeach(list, pvoid) {
 * 	file_t *pfile = (filt_t*)pvoid;
 *	deal_with_file(pfile);		
 * }
 * -----------------------------------------------------
 */
#define gfs_list_foreach(__list, __elem) 				\
	if (__list != NULL && __list->size > 0)			\
		listnode_t *__tmp;				\
		for (__tmp = __list->head->next;			\
		       __tmp && __elem = __tmp->elem; 		\
		       __tmp = __tmp->next)


extern void gfs_list_init(gfs_list_t **list);
extern void gfs_list_insert(gfs_list_t *list, void* elem, uint16_t pos);
/*
this two are replaced by two "define" above with a esaier implementation
extern void gfs_list_push_back(gfs_list_t *list, void* elem);
extern void gfs_list_push_front(gfs_list_t *list, void* elem);
*/
extern void gfs_list_delete(gfs_list_t *list, void *elem);
extern listnode_t *gfs_list_find(gfs_list_t *list, void *elem);
extern listnode_t *gfs_list_get(gfs_list_t *list, int pos);
/* I am not sure the following two function is necessary while we hava gfs_list_foreach */
/* If you are sure it is of no use, you can comment them 			          */
extern listnode_t *gfs_list_findFirst(gfs_list_t *list);
extern listnode_t *gfs_list_findNext(listnode_t *node);
extern void gfs_list_free(gfs_list_t **list); 
/* extern void gfs_list_print(gfs_list_t *list); */


#endif
