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


int
ask_chksvc_open(int chk, const char *name, int oflags, mode_t mode) {
	CLIENT *cl;
	open_args args;
	int *res;

	cl = (CLIENT*)(gfs_list_get(chk_clnts, chk)->elem);

	args.path = (char*)malloc(strlen(name) + 1);
	strcpy(args.path, name);
	args.oflags = oflags;
	args.mode = mode;

	res = ask_chk_open_1(&args, cl);
	free(args.path);

	return *res;
}

int
ask_chksvc_close(int chk, int fd) {
	CLIENT *cl;
	close_args args;

	cl = (CLIENT*)(gfs_list_get(chk_clnts, chk)->elem);

	args.fd = fd;

	return *ask_chk_close_1(&args, cl);
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


chk_info*
ask_mstr_read_1_svc(read_args *args, struct svc_req *req) {
	static chk_info info = {NULL, NULL, 0};
	if (info.name == NULL) {
		info.name = (char*)malloc(65);
	}
	if (info.ip == NULL) {
		info.ip = (char*)malloc(16);
	}

	on_clnt_read(args->fd, &info);
	printf("on_clnt_read, name %s, ip %s, fd %d\n", info.name, info.ip, info.fd);
	return &info;
}


chk_info*
ask_mstr_write_1_svc(write_args *args, struct svc_req *req) {
	static chk_info info = {NULL, NULL, 0};
	if (info.name == NULL) {
		info.name = (char*)malloc(65);
	}
	if (info.ip == NULL) {
		info.ip = (char*)malloc(16);
	}
	
	on_clnt_write(args->fd, &info);
	printf("ask_mstr_write_1_svc, name %s, ip %s, fd %d\n", info.name, info.ip, info.fd);

	return &info;
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
