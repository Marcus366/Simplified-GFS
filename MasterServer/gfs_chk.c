#include "gfs_list.h"
#include "gfs_chk.h"
#include <stdlib.h>

void gfs_chk_new(gfs_chk_t **chk) {
	*chk = (gfs_chk_t*)malloc(sizeof(gfs_chk_t));
	(*chk)->chk_fd = -1;
	(*chk)->uuid = 0;
}


void gfs_chk_free(gfs_chk_t **chk) {
	free(*chk);
	*chk = NULL;
}


void gfs_chksvc_new(gfs_chksvc_t **chksvc) {
	*chksvc = (gfs_chksvc_t*)malloc(sizeof(gfs_chksvc_t));
	(*chksvc)->ip[0] = '\0';
	gfs_list_init((&(*chksvc)->chks));
}

void gfs_chksvc_free(gfs_chksvc_t **chksvc) {
	gfs_list_free((&(*chksvc)->chks));
	free(*chksvc);
	*chksvc = NULL;
}
