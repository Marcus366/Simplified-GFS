#include "filetree.h"
#include "file.h"
#include <stdlib.h>
#include <string.h>


void create_node(node_t *father, file_t *file) { 
	node_t *node;

	node = (node_t*) malloc(sizeof(node_t));
	node->file = file;
	node->father = father;
	gfs_list_init(&node->child);
	if( father != NULL)
		gfs_list_push_back(father->child, (void*)node);
}




void delete_node(node_t **node) {
	node_t *father;

	while((*node)->child->size != 0){
		listnode_t *listnode = gfs_list_findFirst((*node)->child);
		node_t *tnode = (node_t*) listnode->elem;
		delete_Node(&tnode);
	}

	father = (*node)->father;
	gfs_list_delete(father->child, *node);
	free_Node(node);
	node = NULL;
}



node_t* find_node(node_t *root, file_t *file) {
	listnode_t *listnode;

	listnode = linklist_findFirst((root)->child);
	while( listnode != NULL) {
		node_t *tnode = (node_t*)listnode->elem;
		if( file_equal(tnode->file, file) ) {
			return tnode;
		}
		listnode = listnode->next;
	}

	listnode = gfs_list_findFirst((root)->child);

	while( listnode != NULL) {
		node_t *tnode = (node_t*)listnode->elem;
		node_t* result = find_node(tnode, file);
		if(result != NULL)return result;
		listnode = listnode->next;
	}
	return NULL;
}


node_t* find_node_by_name(node_t *root, char *name) {
	listnode_t *listnode;

	listnode = linklist_findFirst((root)->child);

	while( listnode != NULL) {
		node_t *tnode = (node_t*)listnode->elem;
		if( strcmp(name, tnode->file->name) == 0 ) {
			return tnode;
		}
		listnode = listnode->next;
	}
	
	listnode = linklist_findFirst((root)->child);
	
	while( listnode != NULL) {
		node_t *tnode = (node_t*)listnode->elem;
		file_t* file;
		file_new(&file, name, 1);             //type should be changed
		node_t* result = find_node(tnode, file);
		if(result != NULL)return result;
		listnode = listnode->next;
	}
	return NULL;
}


file_t* get_file_by_path(node_t *root, const char *full_path) {
	node_t* node = NULL;
	int count,st;

	node = root;
	count = 0;
	st = 0;
	if(full_path[0] == '/') {
		count++;
		st++;
	}
	while(full_path[count] != '\0') {
		if(full_path[count] == '/') {
			char temp[33];
			strncpy(temp, full_path + st, count - st);
			node = find_node_by_name(node, temp);
			st = count + 1;
		}
		count++;
	}
	char temp[33];
	strncpy(temp, full_path + st, count - st);
	node = find_node_by_name(node, temp);

	return node->file;
}

void free_node(node_t **node) {
	file_free(&((*node)->file));
	gfs_list_free(&((*node)->child));
	(*node)->father = NULL;
	free(*node);
	node = NULL;
}
