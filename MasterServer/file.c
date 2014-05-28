#include "file.h"
#include "string.h"

file_t* get_file_by_path(const char *full_path) {

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


