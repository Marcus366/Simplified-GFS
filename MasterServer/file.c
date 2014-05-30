#include "file.h"
#include "string.h"

file_t* get_file_by_path(const char *full_path) {

}



int file_equal(file_t *lhs,file_t *rhs) {
	if(strcmp(lhs->name, rhs->name) != 0) return 0;
	if(lhs->type != rhs->type) return 0;
	return 1;
}

void file_free(file_t **file) {
	free(*file);
	file = NULL;
}


