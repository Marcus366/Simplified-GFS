#include "file.h"
#include "string.h"
#include "file_tree.h"


void file_new(file_t* file, char* name, int type) {
	file = (file_t*)malloc(sizeof(file_t));
	file->name = name;
	file->type = type;
}


int file_equal(file_t *f1,file_t *f2) {
	if(strcmp(f1->name, f2->name) != 0) return 0;
	if(f1->type != f2->type) return 0;
	return 1;
}

void file_free(file_t **file) {
	free(*file);
	file = NULL;
}


void file_create(const char *path, mode_t mode, int type, node_t *root) {
	node_t *node;
	node_t *father;
	file_t *file;

	father = root;
	char temp[33];
	while(full_path[count] != '\0') {
		if(full_path[count] == '/') {
			strncpy(temp, full_path + st, count - st);
			father = find_node_by_name(node, temp);
			st = count + 1;
		}
		count++;
	}
	strncpy(temp, full_path + st, count - st);

	file_new(file, temp, type);
	node = create_node(father, file);
}


