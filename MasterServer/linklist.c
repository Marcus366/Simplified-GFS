#include "linklist.h"
#include <stdlib.h>
#include <stdio.h>


void linklist_init(linklist_t **list) {
	*list = (linklist_t*) malloc(sizeof(linklist_t));
	(*list)->head = (listnode_t*) malloc(sizeof(listnode_t));
	(*list)->size = 0;
}


void linklist_insert(linklist_t *list, void* elem, uint16_t pos) {
	if (pos < 0 || pos >= list->size) {
		return ;
	}

	listnode_t *pre, *cur, *insert;

	insert = (listnode_t*) malloc(sizeof(listnode_t));
	insert->elem = elem;

	pre = list->head;
	cur = pre->next;
	while (pos--) {
		pre = pre->next;
		cur = cur->next;
	}
	pre->next = inserting;
	inserting->next = cur;
	list->size++;
}


listnode_t *linklist_find(linklist_t *list, void* elem) {
	listnode_t *listnode = list->head;
	while (listnode->next != NULL && listnode->elem != elem) {
		listnode = listnode->next;
	}
	return listnode;
}


listnode_t* linklist_findFirst(linklist_t *list, void* elem) {
	return list->head->next;
}


listnode_t* linklist_findNext(listnode_t *node) {
	return node->next;
}


void linklist_push_back(linklist_t *list, void* elem) {
	listnode_t *listnode = list->head;
	listnode_t *inserting = (listnode_t*) malloc(sizeof(listnode_t));
	inserting->elem = elem;
	while (listnode->next != NULL) {
		listnode = listnode->next;
	}
	listnode->next = inserting;
	list->size++;
}


void linklist_push_front(linklist_t *list, void* elem) {
	listnode_t *headnode = list->head;
	listnode_t *firstnode = list->head->next;
	listnode_t *inserting = (listnode_t*) malloc(sizeof(listnode_t));
	inserting->elem = elem;
	headnode->next = inserting;
	inserting->next = firstnode;
	list->size++;
}


void linklist_delete(linklist_t *list, void* elem) {
	listnode_t *listnode = list->head;
	listnode_t *listnode2 = list->head->next;
	while (listnode2 != NULL && listnode2->elem != elem)
	{
		listnode = listnode->next;
		listnode2 = listnode2->next;
	} 
	listnode->next = listnode2->next;
	free(listnode2);
}


void linklist_free(linklist_t **list) {
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


void linklist_print(linklist_t *list) {
	listnode_t *listnode = list->head->next;
	while (listnode != NULL) {
		printf("%d\n",(int)listnode->elem);
		listnode = listnode->next;
	}
}