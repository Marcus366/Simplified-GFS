#include "gfs_list.h"
#include <stdlib.h>
#include <stdio.h>


void gfs_list_init(gfs_list_t **list) {
	*list = (gfs_list_t*) malloc(sizeof(gfs_list_t));
	(*list)->head = (listnode_t*) malloc(sizeof(listnode_t));
	(*list)->head->next = NULL;
	(*list)->head->elem = NULL;
	(*list)->size = 0;
}


void gfs_list_insert(gfs_list_t *list, void* elem, uint16_t pos) {
	listnode_t *pre;

	pre = list->head;
	if (elem != NULL && pos >= 0 && pos <= list->size) {
		listnode_t *inserting = (listnode_t*) malloc(sizeof(listnode_t));
		inserting->elem = elem;
		while (pos--) {
			pre = pre->next;
		}
		inserting->next = pre->next;
		pre->next = inserting;
		list->size++;
	}
}


listnode_t *gfs_list_find(gfs_list_t *list, void* elem) {
	listnode_t *listnode = list->head;
	while (listnode->next != NULL && listnode->elem != elem) {
		listnode = listnode->next;
	}
	return listnode;
}


listnode_t* gfs_list_get(gfs_list_t *list, int pos) {
	listnode_t *cur;

	if (pos < 0 || pos > list->size) {
		cur = NULL;
	}	else {
		cur = list->head;
		while (pos--) {
			cur = cur->next;
		}
	}

	return NULL;
}


listnode_t *gfs_list_findFirst(gfs_list_t *list) {
	return list->head->next;
}


listnode_t *gfs_list_findNext(listnode_t *node) {
	return node->next;
}

/*
void gfs_list_push_back(gfs_list_t *list, void* elem) {
	listnode_t *listnode = list->head;
	listnode_t *inserting = (listnode_t*) malloc(sizeof(listnode_t));
	inserting->elem = elem;
	while (listnode->next != NULL) {
		listnode = listnode->next;
	}
	listnode->next = inserting;
	list->size++;
}


void gfs_list_push_front(gfs_list_t *list, void* elem) {
	listnode_t *headnode = list->head;
	listnode_t *firstnode = list->head->next;
	listnode_t *inserting = (listnode_t*) malloc(sizeof(listnode_t));
	inserting->elem = elem;
	headnode->next = inserting;
	inserting->next = firstnode;
	list->size++;
}
*/

void gfs_list_delete(gfs_list_t *list, void *elem) {
	listnode_t *pre, *cur;

	pre = list->head;
	cur = pre->next;
	while (cur != NULL && cur->elem != elem) {
		pre = pre->next;
		cur = cur->next;
	} 
	
	if (cur != NULL) {
		--list->size;
		pre->next = cur->next;
		free(cur);
	}
}


void gfs_list_free(gfs_list_t **list) {
	listnode_t *listnode = (*list)->head->next;
	listnode_t *deleting = listnode;
	while (listnode != NULL){
		deleting = listnode;
		listnode = listnode->next;
		free(deleting);
	}
	free((*list)->head);
	free(*list);
	*list = NULL;
}
/*
void gfs_list_print(gfs_list_t *list) {
	listnode_t *listnode = list->head->next;
	while (listnode != NULL) {
		printf("%d\n",(int)listnode->elem);
		listnode = listnode->next;
	}
}
*/
