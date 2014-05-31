#include "gfs_rpc.h"
#include "gfs_mstr_svc.h"


static struct timeval TIMEOUT = { 25, 0 };


int*
ask_chk_open_1(open_args *argp, CLIENT *clnt)
{
	static int clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, ask_chk_open,
		(xdrproc_t) xdr_open_args, (caddr_t) argp,
		(xdrproc_t) xdr_int, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}


int*
ask_chk_close_1(close_args *argp, CLIENT *clnt)
{
	static int clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, ask_chk_close,
		(xdrproc_t) xdr_close_args, (caddr_t) argp,
		(xdrproc_t) xdr_int, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}


#ifdef ask_chk_open
#undef ask_chk_open
#endif

#ifdef ask_chk_close
#undef ask_chk_close
#endif

int
ask_chk_open(const char *name, int oflags, mode_t mode) {
	return -1;
	/* not implement */
}

int
ask_chk_close(int fd) {
	return -1;
	/* not implement */
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


int*
ask_mstr_read_1_svc(read_args *args, struct svc_req *req) {
	static int res;

	res = on_clnt_read(args->fd, args->buf, args->count);

	return &res;
}


int*
ask_mstr_write_1_svc(write_args *args, struct svc_req *req) {
	static int res;

	res = on_clnt_write(args->fd, args->buf, args->nbytes);

	return &res;
}


int*
reg_chk_1_svc(char **arg, struct svc_req *req) {
	static int res = 0;

	printf("remote chk register, ip: %s\n", *arg);
	on_chk_reg(*arg);

	return &res;
}


int*
unreg_chk_1_svc(char **arg, struct svc_req *req) {
	static int res = 0;

	on_chk_unreg(*arg);

	return &res;
}
