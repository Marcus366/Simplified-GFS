#include "gfs_rpc.h"
#include "gfs_mstr.h"


int*
ask_chk_open_1(open_args *args, CLIENT *cl) {
	return NULL;
}


int*
ask_chk_close_1(close_args *args, CLIENT *cl) {
	return NULL;
}

int*
ask_mstr_open_1_svc(open_args *args, struct svc_req *req) {
	static int fd;

	fd = on_clnt_open(args->path, args->oflags, args->mode);

	return &fd;
}


int*
ask_mstr_close_1_svc(close_args *args, struct svc_req *req) {
	static int fd;

	fd = on_clnt_close(args->fd);

	return &fd;
}


long*
ask_mstr_read_1_svc(read_args *args, struct svc_req *req) {
	static long a;

	a = 0;

	return &a;
}


long*
ask_mstr_write_1_svc(write_args *args, struct svc_req *req) {
	static long a;

	a = 0;

	return &a;
}
