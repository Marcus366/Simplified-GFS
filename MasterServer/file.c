#include "file.h"
#include "gfs_filetree.h"
#include "gfs_chk.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

file_t *fds[MAX_FILE_SIZE];			
int fd_count;


void file_new(file_t **file, const char* name, int type) {
	*file = (file_t*)malloc(sizeof(file_t));

	(*file)->type = type;

	strncpy((*file)->name, name, 32);
	((*file)->name)[33] = 0;

	gfs_list_init(&((*file)->chunks));
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


file_t *file_create(const char *path, mode_t mode, int type, gfs_node_t *root) {
	gfs_node_t *node;
	gfs_node_t *father;
	file_t *file;
	int count = 0,st = 0;
	char temp[33];
	father = root;

	if(path[0] == '/') {
		count++;
		st++;
	}
	while(path[count] != '\0') {
		if(path[count] == '/') {
			strncpy(temp, path + st, count - st);
			printf("bffn\n");
			father = gfs_find_node_by_name(father, temp);
			st = count + 1;
		}
		count++;
	}
	strncpy(temp, path + st, count - st );
	temp[count - st] = '\0';
	//printf("path:%s temp:%s st:%d count:%d\n", path, temp, st, count);
	file_new(&file, temp, type);
	gfs_create_node(&node, father, file);
	return file;
}


int get_fd(file_t* file){
	if (file == NULL) {
		return -1;
	}
	unsigned int seed = 13131; // 31 131 1313 13131 131313 etc..
 	unsigned int hash = 0; 
	char* str = file->name;

	while (*str) {
		hash = hash * seed + (*str++);
	}

	int fd = (hash & 0x7FFFFFFF);
	fd %= MAX_FILE_SIZE;
	while (fds[fd] != NULL) {
		fd++;
		fd %= MAX_FILE_SIZE;
	}

	printf("this is get_fd fd: %d\n", fd);
	return fd;
}
