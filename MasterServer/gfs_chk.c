#include "gfs_chk.h"
#include <stdlib.h>

void gfs_chk_new(gfs_chk_t **chk) {
	*chk = (gfs_chk_t*)malloc(sizeof(gfs_chk_t));
	(*chk)->chk_fd = -1;
}


void gfs_chk_free(gfs_chk_t **chk) {
	free(*chk);
	*chk = NULL;
}
