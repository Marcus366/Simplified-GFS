#include "linklist.h"
#include <stdlib.h>
#include <stdio.h>


void linklist_init(linklist_t **list) {
	*list = (linklist_t*) malloc(sizeof(linklist_t));
	(*list)->head = (linknode_t*) malloc(sizeof(linknode_t));
	(*list)->size = 0;
}


void linklist_insert(linklist_t *list, listnode_t *node, uint16_t pos) {
	listnode_t *listnode = list->head;
	listnode_t *listnode2 = listnode->next;
	while (pos--) {
		listnode = listnode->next;
		listnode2 = listnode2->next;
	}
	listnode->next = node;
	node->next = listnode2;
}


void linklist_push_back(linklist_t *list, listnode_t *node) {
	listnode_t *listnode = list->head;
	while (listnode->next != NULL) {
		listnode->next = node;
	}
}


void linklist_push_front(linklist_t *list, listnode_t *node) {
	listnode_t *headnode = list->head;
	listnode_t *firstnode = list->head->next;
	headnode->next = node;
	node->next = firstnode;
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

void linklist_print(linklist *list) {
	listnode_t *listnode = list->head->next;
	while (listnode->next != NULL) {
		printf("%d\n",(int)listnode->elem);
		listnode = listnode->next;
	}
}