#include "gfs_rpc.h"
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#define CHK_SIZE 1024

static struct timeval TIMEOUT = { 25, 0 };


int*
reg_chk_1(char **argp, CLIENT *clnt) {
	static int clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, reg_chk,
		(xdrproc_t) xdr_wrapstring, (caddr_t) argp,
		(xdrproc_t) xdr_int, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}


int*
unreg_chk_1(char **argp, CLIENT *clnt) {
	static int clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, unreg_chk,
		(xdrproc_t) xdr_wrapstring, (caddr_t) argp,
		(xdrproc_t) xdr_int, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}


int*
ask_chk_open_1_svc(open_args *args, struct svc_req *req) {
	static int fd;

	printf("ask_chk_open_1_svc, path: %s\n", args->path);
	fd = open(args->path, args->oflags, args->mode);

	return &fd;
}


int*
ask_chk_close_1_svc(close_args *args, struct svc_req *req) {
	static int res;

	printf("ask_chk_close_1_svc fd: %d\n", args->fd);
	res = close(args->fd);

	return &res;
}


int*
ask_chk_write_1_svc(write_args *args, struct svc_req *req) {
	static int res;
	struct stat file_stat;

	printf("ask_chk_write_svc: %s\n", args->buf);
	if (fstat(args->fd, &file_stat) == -1) {
		res = -1;
		return &res;
	}

	printf("ask_chk_write_svc: chk_size %ld\n", file_stat.st_size);
	if (args->nbytes + file_stat.st_size < CHK_SIZE) {
		res = write(args->fd, args->buf, args->nbytes);
	} else {
		res = write(args->fd, args->buf, CHK_SIZE - file_stat.st_size);
	}

	return &res;
}


read_res*
ask_chk_read_1_svc(read_args *args, struct svc_req *req) {
	static read_res res = {0, NULL};

	if (res.buf != NULL) {
		free(res.buf);
	}
	res.buf = (char*)malloc(args->count);
	res.ssize = read(args->fd, res.buf, args->count);
	
	return &res;
}
