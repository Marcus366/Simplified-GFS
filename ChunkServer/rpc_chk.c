#include "gfs_rpc.h"
#include <fcntl.h>


static struct timeval TIMEOUT = { 25, 0 };


int *
reg_chk_1(char **argp, CLIENT *clnt)
{
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


int *
unreg_chk_1(char **argp, CLIENT *clnt)
{
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
	/* not implement */
	return NULL;
}

int*
ask_chk_read_1_svc(read_args *args, struct svc_req *req) {
	/* not implement */
	return NULL;
}