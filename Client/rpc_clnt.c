#include <memory.h> /* for memset */
#include "gfs_rpc.h"


static struct timeval TIMEOUT = { 25, 0 };

int*
ask_mstr_open_1(open_args *argp, CLIENT *clnt) {
	static int clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, ask_mstr_open,
		(xdrproc_t) xdr_open_args, (caddr_t) argp,
		(xdrproc_t) xdr_int, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

int*
ask_mstr_close_1(close_args *argp, CLIENT *clnt) {
	static int clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, ask_mstr_close,
		(xdrproc_t) xdr_close_args, (caddr_t) argp,
		(xdrproc_t) xdr_int, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

chk_info*
ask_mstr_read_1(read_args *argp, CLIENT *clnt) {
	static chk_info clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, ask_mstr_read,
		(xdrproc_t) xdr_read_args, (caddr_t) argp,
		(xdrproc_t) xdr_chk_info, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

chk_info*
ask_mstr_write_1(write_args *argp, CLIENT *clnt) {
	static chk_info clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, ask_mstr_write,
		(xdrproc_t) xdr_write_args, (caddr_t) argp,
		(xdrproc_t) xdr_chk_info, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

int*
ask_chk_write_1(write_args *argp, CLIENT *clnt) {
	static int clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, ask_chk_write,
		(xdrproc_t) xdr_write_args, (caddr_t) argp,
		(xdrproc_t) xdr_int, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

read_res*
ask_chk_read_1(read_args *argp, CLIENT *clnt) {
	static read_res clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, ask_chk_read,
		(xdrproc_t) xdr_read_args, (caddr_t) argp,
		(xdrproc_t) xdr_read_res, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}