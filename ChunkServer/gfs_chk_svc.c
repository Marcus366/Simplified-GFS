/**
 * Here is Chunk_Server start up code
 * on start up, chunk server connect to master,
 * tell him "I am want to join the cluster" and send port number to him
 * then chunk server run loop to wait for client
 */
#include "gfs_rpc.h"
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


CLIENT *cl;

static int
init_clnt(char **argv) {
	if ((cl = clnt_create(argv[2], CHK_MSTR_PROG, VERSION, "tcp")) == NULL) {
		fprintf(stderr, "create clnt error\n");
		return -1;
	}

	reg_chk_1(&argv[1], cl);
	return 0;
}


static void
mstr_chk_prog_1(struct svc_req *rqstp, register SVCXPRT *transp) {
	union {
		open_args ask_chk_open_1_arg;
		close_args ask_chk_close_1_arg;
	} argument;
	char *result;
	xdrproc_t _xdr_argument, _xdr_result;
	char *(*local)(char *, struct svc_req *);

	switch (rqstp->rq_proc) {
	case NULLPROC:
		(void) svc_sendreply (transp, (xdrproc_t) xdr_void, (char *)NULL);
		return;

	case ask_chk_open:
		_xdr_argument = (xdrproc_t) xdr_open_args;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) ask_chk_open_1_svc;
		break;

	case ask_chk_close:
		_xdr_argument = (xdrproc_t) xdr_close_args;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) ask_chk_close_1_svc;
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
init_svc() {
	register SVCXPRT *transp;

	pmap_unset (MSTR_CHK_PROG, VERSION);

	transp = svcudp_create(RPC_ANYSOCK);
	if (transp == NULL) {
		fprintf (stderr, "%s", "cannot create udp service.");
		exit(1);
	}
	if (!svc_register(transp, MSTR_CHK_PROG, VERSION, mstr_chk_prog_1, IPPROTO_UDP)) {
		fprintf (stderr, "%s", "unable to register (MSTR_CHK_PROG, VERSION, udp).");
		exit(1);
	}

	transp = svctcp_create(RPC_ANYSOCK, 0, 0);
	if (transp == NULL) {
		fprintf (stderr, "%s", "cannot create tcp service.");
		exit(1);
	}
	if (!svc_register(transp, MSTR_CHK_PROG, VERSION, mstr_chk_prog_1, IPPROTO_TCP)) {
		fprintf (stderr, "%s", "unable to register (MSTR_CHK_PROG, VERSION, tcp).");
		exit(1);
	}
	svc_run ();
	fprintf (stderr, "%s", "svc_run returned");
	exit (1);
}


int
main(int argc, char **argv) {
	if (argc != 3) {
		fprintf(stderr, "usage: %s <CHK IP> <MSTR IP>\n", argv[0]);
		return -1;
	}

	if (init_clnt(argv) == -1) {
		fprintf(stderr, "init clnt error\n");
		return -1;
	}

	init_svc();
	/* NEVER RETURN */

	return -1;
}