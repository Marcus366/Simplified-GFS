#include "file.h"
#include "gfs_filetree.h"
#include "gfs_chk.h"
#include <string.h>
#include <stdlib.h>

file_t *fds[MAX_FILE_SIZE];			
int fd_count;


void file_new(file_t **file, const char* name, int type) {
	*file = (file_t*)malloc(sizeof(file_t));
	(*file)->type = type;
	gfs_list_init(&((*file)->chunks));
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


file_t *file_create(const char *path, mode_t mode, int type, gfs_node_t *root) {
	gfs_node_t *node;
	gfs_node_t *father;
	file_t *file;
	int count = 0,st = 0;
	char temp[33];

	father = root;
	while(path[count] != '\0') {
		if(path[count] == '/') {
			strncpy(temp, path + st, count - st);
			father = gfs_find_node_by_name(node, temp);
			st = count + 1;
		}
		count++;
	}
	strncpy(temp, path + st, count - st);

	file_new(&file, temp, type);
	gfs_create_node(&node, father, file);
	return file;
}


/*
int binary_search_fds(int fd){
	int st = 0, ed = fd_count - 1, mid;
    while(st <= ed){			//binary search
    	mid = (ed + st) / 2;
    	if(fd == fds[mid]) return mid;
    	else if(fd < fds[mid]) {
    		ed = mid - 1;
    	}
    	else {
    		st = mid + 1;
    	}
    }
    return -1;
}
*/


int get_fd(file_t* file){
	unsigned int seed = 13131; // 31 131 1313 13131 131313 etc..
 	unsigned int hash = 0; 
	char* str = file->name;

	while (*str) {
		hash = hash * seed + (*str++);
	}

	int fd = (hash & 0x7FFFFFFF);

	while(fds[fd] != NULL){
		fd++;
	}
	return fd;
}
