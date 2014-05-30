#include "file.h"
#include "filetree.h"
#include <string.h>
#include <stdlib.h>


void file_new(file_t **file, char* name, int type) {
	*file = (file_t*)malloc(sizeof(file_t));
	(*file)->type = type;

	strncpy((*file)->name, name, 32);
	((*file)->name)[33] = 0;
}


int file_equal(file_t *lhs,file_t *rhs) {
	if(strcmp(lhs->name, rhs->name) != 0) return 0;
	if(lhs->type != rhs->type) return 0;
	return 1;
}


void file_free(file_t **file) {
	free(*file);
	*file = NULL;
}


void file_create(const char *path, mode_t mode, int type, node_t *root) {
	node_t *node;
	node_t *father;
	file_t *file;
	int count = 0,st = 0;
	char temp[33];

	father = root;
	while(path[count] != '\0') {
		if(path[count] == '/') {
			strncpy(temp, path + st, count - st);
			father = find_node_by_name(node, temp);
			st = count + 1;
		}
		count++;
	}
	strncpy(temp, path + st, count - st);

	file_new(&file, temp, type);
	create_node(father, file);
}
