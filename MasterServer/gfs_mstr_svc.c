#include "gfs_rpc.h"
#include "gfs_list.h"
#include "gfs_filetree.h"
#include "gfs_chk.h"
#include "rpc_mstr.h"
#include "file.h"
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
gfs_list_t *chk_clnts;
gfs_node_t *filetree_root;


static void
init_chk_svcs() {
	gfs_list_init(&chk_svcs);
	gfs_list_init(&chk_clnts);
}

static void
init_filetree_root() {
	file_t *file;
	file_new(&file, "root", FILE_TYPE_FILE);
	gfs_create_node(&filetree_root, NULL, file);
}

static void
init_fds() {
	fd_count = 0;
	int i;
	for(i = 0;i<MAX_FILE_SIZE;++i) {
		fds[i] = NULL;
	}
}


int
main (int argc, char **argv) {
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
	init_filetree_root();
	init_fds();

	svc_run ();
	fprintf (stderr, "%s", "svc_run returned");
	exit (1);
	/* NOTREACHED */
}


int on_clnt_open(const char *path, int oflags, mode_t mode) {
	file_t *file;
	file = gfs_get_file_by_path(filetree_root, path);
	if(file == NULL && oflags & O_CREAT) {
		file = file_create(path, mode, FILE_TYPE_FILE, filetree_root);
		gfs_chk_t *chk;
		gfs_chk_new(&chk);
		gfs_list_push_back(file->chunks, (void*)chk);
	}
	int fd = get_fd(file);
	if(fd == -1) return -1;
	gfs_filetree_print(filetree_root);
	printf("path: %s\n", path);
	gfs_chk_t *chk = (gfs_chk_t*)(gfs_list_findFirst(file->chunks)->elem);
	char name[64];
	sprintf(name,"%llu",chk->uuid);
	printf("uuid:%s\n", name);
	//ask_chksvc_open(0, name, oflags, mode);
	/* not implement */
	return fd;
}


int on_clnt_close(int fd) {
	printf("close fd: %d\n", fd);
	return 0;
}


chk_info on_clnt_read(int fd) {
	chk_info info = {NULL, NULL, 0};
	/* not impelement */
	return info;
}


chk_info on_clnt_write(int fd) {
	/* not implement */
	chk_info info = {NULL, NULL, 0};

	return info;
}

int on_chk_reg(char *ip) {
	CLIENT *cl;

	printf("on_chk_reg, reg ip: %s\n", ip);
	cl = clnt_create(ip, MSTR_CHK_PROG, VERSION, "tcp");
	if (cl == NULL) {
		fprintf(stderr, "on_chk_reg, reg ip(%s) failed\n", ip);
		return -1;
	}
	gfs_list_push_back(chk_clnts, cl);

	char *chksvc_ip = (char*)malloc(strlen(ip) + 1);
	strcpy(chksvc_ip, ip);
	gfs_list_push_back(chk_svcs, chksvc_ip);

	return 0;
}

int on_chk_unreg(char *ip) {
	/* not implement */

	return 0;
}
