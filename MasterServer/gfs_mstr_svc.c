#include "gfs_rpc.h"
#include "gfs_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <rpc/pmap_clnt.h>
#include <string.h>
#include <memory.h>
#include <sys/socket.h>
#include <netinet/in.h>


#ifndef SIG_PF
#define SIG_PF void(*)(int)
#endif


static void
clnt_mstr_prog_1(struct svc_req *rqstp, register SVCXPRT *transp) {
	union {
		open_args ask_mstr_open_1_arg;
		close_args ask_mstr_close_1_arg;
		read_args gfs_read_1_arg;
		write_args gfs_write_1_arg;
	} argument;
	char *result;
	xdrproc_t _xdr_argument, _xdr_result;
	char *(*local)(char *, struct svc_req *);

	switch (rqstp->rq_proc) {
	case NULLPROC:
		(void) svc_sendreply (transp, (xdrproc_t) xdr_void, (char *)NULL);
		return;

	case ask_mstr_open:
		_xdr_argument = (xdrproc_t) xdr_open_args;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) ask_mstr_open_1_svc;
		break;

	case ask_mstr_close:
		_xdr_argument = (xdrproc_t) xdr_close_args;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) ask_mstr_close_1_svc;
		break;

	case ask_mstr_read:
		_xdr_argument = (xdrproc_t) xdr_read_args;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) ask_mstr_read_1_svc;
		break;

	case ask_mstr_write:
		_xdr_argument = (xdrproc_t) xdr_write_args;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) ask_mstr_write_1_svc;
		break;

	default:
		svcerr_noproc (transp);
		return;
	}
	memset ((char *)&argument, 0, sizeof (argument));
	if (!svc_getargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		svcerr_decode (transp);
		return;
	}
	result = (*local)((char *)&argument, rqstp);
	if (result != NULL && !svc_sendreply(transp, (xdrproc_t) _xdr_result, result)) {
		svcerr_systemerr (transp);
	}
	if (!svc_freeargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		fprintf (stderr, "%s", "unable to free arguments");
		exit (1);
	}
	return;
}


static void
chk_mstr_prog_1(struct svc_req *rqstp, register SVCXPRT *transp) {
	union {
		char *reg_chk_1_arg;
		char *unreg_chk_1_arg;
	} argument;
	char *result;
	xdrproc_t _xdr_argument, _xdr_result;
	char *(*local)(char *, struct svc_req *);

	switch (rqstp->rq_proc) {
	case NULLPROC:
		(void) svc_sendreply (transp, (xdrproc_t) xdr_void, (char *)NULL);
		return;

	case reg_chk:
		_xdr_argument = (xdrproc_t) xdr_wrapstring;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) reg_chk_1_svc;
		break;

	case unreg_chk:
		_xdr_argument = (xdrproc_t) xdr_wrapstring;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) unreg_chk_1_svc;
		break;

	default:
		svcerr_noproc (transp);
		return;
	}
	memset ((char *)&argument, 0, sizeof (argument));
	if (!svc_getargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		svcerr_decode (transp);
		return;
	}
	result = (*local)((char *)&argument, rqstp);
	if (result != NULL && !svc_sendreply(transp, (xdrproc_t) _xdr_result, result)) {
		svcerr_systemerr (transp);
	}
	if (!svc_freeargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		fprintf (stderr, "%s", "unable to free arguments");
		exit (1);
	}
	return;
}


gfs_list_t *chk_svcs;


static void
init_chk_svcs() {
	gfs_list_init(&chk_svcs);
}


int
main (int argc, char **argv)
{
	register SVCXPRT *transp;

	pmap_unset (CLNT_MSTR_PROG, VERSION);
	pmap_unset (CHK_MSTR_PROG, VERSION);

	transp = svcudp_create(RPC_ANYSOCK);
	if (transp == NULL) {
		fprintf (stderr, "%s", "cannot create udp service.");
		exit(1);
	}
	if (!svc_register(transp, CLNT_MSTR_PROG, VERSION, clnt_mstr_prog_1, IPPROTO_UDP)) {
		fprintf (stderr, "%s", "unable to register (CLNT_MSTR_PROG, VERSION, udp).");
		exit(1);
	}
	if (!svc_register(transp, CHK_MSTR_PROG, VERSION, chk_mstr_prog_1, IPPROTO_UDP)) {
		fprintf (stderr, "%s", "unable to register (CHK_MSTR_PROG, VERSION, udp).");
		exit(1);
	}

	transp = svctcp_create(RPC_ANYSOCK, 0, 0);
	if (transp == NULL) {
		fprintf (stderr, "%s", "cannot create tcp service.");
		exit(1);
	}
	if (!svc_register(transp, CLNT_MSTR_PROG, VERSION, clnt_mstr_prog_1, IPPROTO_TCP)) {
		fprintf (stderr, "%s", "unable to register (CLNT_MSTR_PROG, VERSION, tcp).");
		exit(1);
	}
	if (!svc_register(transp, CHK_MSTR_PROG, VERSION, chk_mstr_prog_1, IPPROTO_TCP)) {
		fprintf (stderr, "%s", "unable to register (CHK_MSTR_PROG, VERSION, tcp).");
		exit(1);
	}

	init_chk_svcs();

	svc_run ();
	fprintf (stderr, "%s", "svc_run returned");
	exit (1);
	/* NOTREACHED */
}


int on_clnt_open(const char *path, int oflags, mode_t mode) {
	printf("path: %s\n", path);
	/* not implement */
	return 0;
}


int on_clnt_close(int fd) {
	/* not implement */
	return 0;
}


ssize_t on_clnt_read(int fd, void *buf, size_t count) {

	return 0;
}


ssize_t on_clnt_write(int fd, const void *buf, size_t nbytes) {
	/* not implement */
	char *pbuf;
	pbuf = (char*)malloc(nbytes + 1);
	memcpy(pbuf, buf, nbytes);
	pbuf[nbytes] = 0;
	printf("%s\n", pbuf);
	return nbytes;
}

int on_chk_reg(char *ip) {

	return 0;
}

int on_chk_unreg(char *ip) {
	return 0;
}
