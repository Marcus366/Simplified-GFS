#include "gfs_operation.h"
#include "filetree.h"
#include "file.h"


int gfs_open(const char *path, int oflags, mode_t mode){
	if (oflags & O_CREAT) {
		node_t *node;

		file_create( path, mode, FILE_TYPE_FILE, node);
	}
}

int gfs_close(int fd) {
	
}


ssize_t gfs_read(int fd, void *buf, size_t count){



}


ssize_t gfs_write(int fd, const void *buf, size_t nbytes){

}
