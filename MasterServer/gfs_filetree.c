#include "gfs_filetree.h"
#include "file.h"
#include "gfs_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void gfs_create_node(gfs_node_t **node, gfs_node_t *father, file_t *file) { 
	*node = (gfs_node_t*) malloc(sizeof(gfs_node_t));
	(*node)->file = file;
	(*node)->father = father;
	gfs_list_init(&((*node)->child));
	if( father != NULL)
		gfs_list_push_back(father->child, (void*)*node);
}


void gfs_delete_node(gfs_node_t **node) {
	gfs_node_t *father;

	while((*node)->child->size != 0) {
		listnode_t *listnode = gfs_list_findFirst((*node)->child);
		gfs_node_t *tnode = (gfs_node_t*) listnode->elem;
		gfs_delete_node(&tnode);
	}
	father = (*node)->father;
	gfs_list_delete(father->child, *node);
	gfs_free_node(node);
	node = NULL;
}


gfs_node_t* gfs_find_node(gfs_node_t *root, file_t *file) {
	listnode_t *listnode;

	listnode = gfs_list_findFirst(root->child);

	while (listnode != NULL) {
		gfs_node_t *tnode = (gfs_node_t*)listnode->elem;
		if (file_equal(tnode->file, file)) {
			return tnode;
		}
		listnode = listnode->next;
	}
	
	listnode = gfs_list_findFirst(root->child);
	
	while (listnode != NULL) {
		gfs_node_t *tnode = (gfs_node_t*)listnode->elem;
		gfs_node_t* result = gfs_find_node(tnode, file);
		if(result != NULL) {
			return result;
		}
		listnode = listnode->next;
	}
	return NULL;
}


gfs_node_t* gfs_find_node_by_name(gfs_node_t *root, char *name) {
	listnode_t *listnode;

	listnode = gfs_list_findFirst(root->child);
	printf("this is ff1 %p\n", listnode);

	while( listnode != NULL) {
		printf("this is ff2\n");
		gfs_node_t *tnode = (gfs_node_t*)listnode->elem;
		printf("this is ff3\n");
		if( strcmp(name, tnode->file->name) == 0 ) {
			return tnode;
		}
		listnode = listnode->next;
	}
	
	printf("this is fnn1\n");
	listnode = gfs_list_findFirst(root->child);

	while( listnode != NULL) {
		gfs_node_t *tnode = (gfs_node_t*)listnode->elem;
		gfs_node_t* result = gfs_find_node_by_name(tnode, name);
		if(result != NULL) {
			return result;
		}
		listnode = listnode->next;
	}
	return NULL;
}


file_t* gfs_get_file_by_path(gfs_node_t *root, const char *full_path) {
	gfs_node_t* node = NULL;
	int count,st;

	node = root;
	count = 0;
	st = 0;
	printf("this is bi\n");
	if (full_path[0] == '/') {
		count++;
		st++;
	}
	printf("this is bw\n");
	while (full_path[count] != '\0') {
		if (full_path[count] == '/') {
			char temp[33];
			printf("this is gf\n");
			strncpy(temp, full_path + st, count - st);
			printf("this is dd\n");
			node = gfs_find_node_by_name(node, temp);
			printf("this is jj\n");
			st = count + 1;
		}
		count++;
		printf("%d\n", count);
	}
	char temp[33];
	printf("this is cpy\n");
	strncpy(temp, full_path + st, count - st);
	printf("this is fn2\n");
	node = gfs_find_node_by_name(node, temp);
	printf("this is fn3\n");
	if (node == NULL) {
		return NULL;
	}
	return node->file;
}

gfs_node_t* gfs_get_node_by_path(gfs_node_t *root, const char *full_path){
	gfs_node_t* node = NULL;
	int count, st;

	node = root;
	count = 0;
	st = 0;
	if (full_path[0] == '/') {
		count++;
		st++;
	}
	while (full_path[count] != '\0') {
		if (full_path[count] == '/') {
			char temp[33];
			strncpy(temp, full_path + st, count - st);
			node = gfs_find_node_by_name(node, temp);
			st = count + 1;
		}
		count++;
	}
	char temp[33];
	strncpy(temp, full_path + st, count - st);
	node = gfs_find_node_by_name(node, temp);

	return node;
}

void gfs_filetree_print(gfs_node_t *root){
	printf("%s\n", root->file->name);
	listnode_t *node;
	node = gfs_list_findFirst(root->child);
	while (node != NULL) {
		gfs_node_t * treenode;
		treenode = node->elem;
		printf("%s's child is %s\n", root->file->name, treenode->file->name);
		gfs_filetree_print(treenode);
		node = node->next;
	}
}

void gfs_free_node(gfs_node_t **node) {
	file_free(&((*node)->file));
	gfs_list_free(&((*node)->child));
	(*node)->father = NULL;
	free(*node);
	node = NULL;
}
