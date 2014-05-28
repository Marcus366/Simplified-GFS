#ifndef __LINKLIST_H__
#define __LINKLIST_H__

#include <stdint.h>


typedef struct listnode_s {
	struct listnode_s   *next;
	void		  		*elem;
} listnode_t;


typedef struct linklist_s {
	struct listnode_s*   head;
	uint16_t 	  size;
} linklist_t;


extern void linklist_init(linklist_t **list);
extern void linklist_insert(linklist_t *list, void* elem, uint16_t pos);
extern void linklist_push_back(linklist_t *list, void* elem);
extern void linklist_push_front(linklist_t *list, void* elem);
extern void linklist_delete(linklist_t *list, void* elem);
extern listnode_t *linklist_find(linklist_t *list, void* elem);
extern listnode_t *linklist_findFirst(linklist_t *list, void* elem);
extern listnode_t *linklist_findNext(listnode_t *node);
extern void linklist_free(linklist_t **list); 
extern void linklist_print(linklist_t *list);

#endif