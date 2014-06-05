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
#include <arpa/inet.h>


#ifndef SIG_PF
#define SIG_PF void(*)(int)
#endif


static void
clnt_mstr_prog_1(struct svc_req *rqstp, register SVCXPRT *transp) {
	union {
		open_args ask_mstr_open_1_arg;
		close_args ask_mstr_close_1_arg;
		read_args ask_mstr_read_1_arg;
		write_args ask_mstr_write_1_arg;
		int ask_mstr_newchk_1_arg;
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
		_xdr_result = (xdrproc_t) xdr_chk_info;
		local = (char *(*)(char *, struct svc_req *)) ask_mstr_read_1_svc;
		break;

	case ask_mstr_write:
		_xdr_argument = (xdrproc_t) xdr_write_args;
		_xdr_result = (xdrproc_t) xdr_chk_info;
		local = (char *(*)(char *, struct svc_req *)) ask_mstr_write_1_svc;
		break;

	case ask_mstr_newchk:
		_xdr_argument = (xdrproc_t) xdr_int;
		_xdr_result = (xdrproc_t) xdr_chk_info;
		local = (char *(*)(char *, struct svc_req *)) ask_mstr_newchk_1_svc;
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
	int i;

	fd_count = 0;
	for (i = 0; i < MAX_FILE_SIZE; ++i) {
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
	int gfs_fd, chk_fd;
	gfs_chk_t *chk;
	char chk_name[65];

	file = gfs_get_file_by_path(filetree_root, path);
	if (file == NULL && (oflags & O_CREAT)) {
		file = file_create(path, mode, FILE_TYPE_FILE, filetree_root);
		gfs_chk_new(&chk);
		inet_aton(gfs_list_findFirst(chk_svcs)->elem, (struct in_addr*)&chk->chk_addr);
		gfs_list_push_back(file->chunks, (void*)chk);
	}
	gfs_fd = get_fd(file);
	if (gfs_fd == -1) {
		return -1;
	}
	fds[gfs_fd] = file;
	gfs_filetree_print(filetree_root);
	printf("path: %s\n", path);
	chk = (gfs_chk_t*)(gfs_list_findFirst(file->chunks)->elem);

	sprintf(chk_name,"%llu",chk->uuid);
	printf("uuid:%s\n", chk_name);
	chk_fd = ask_chksvc_open(0, chk_name, oflags, mode);
	chk->chk_fd = chk_fd;
	/* not implement */
	return gfs_fd;
}


int on_clnt_close(int fd) {
	file_t *file;
	gfs_chk_t *chk;

	printf("close fd: %d\n", fd);
	file = fds[fd];
	chk = (gfs_chk_t*)(gfs_list_findFirst(file->chunks)->elem);
	ask_chksvc_close(0, chk->chk_fd);
	chk->chk_fd = -1;

	return 0;
}


void on_clnt_read(int fd, chk_info *info) {
	file_t* file;
	gfs_chk_t *chk;

	file = fds[fd];
	chk = (gfs_chk_t*)(gfs_list_findFirst(file->chunks)->elem);

	sprintf(info->name, "%llu", chk->uuid);
	sprintf(info->ip, "%u", chk->chk_addr);
	info->fd = chk->chk_fd;

	printf("on_clnt_read, name %s, ip %s, fd %d\n", info->name, info->ip, info->fd);
}


void on_clnt_write(int fd, chk_info *info) {
	file_t* file;
	gfs_chk_t *chk;

	printf("on_clnt_write fd: %d\n", fd);
	file = fds[fd];
	chk = (gfs_chk_t*)(gfs_list_findFirst(file->chunks)->elem);

	sprintf(info->name, "%llu", chk->uuid);
	strcpy(info->ip, inet_ntoa((struct in_addr){chk->chk_addr}));
	info->fd = chk->chk_fd;

	printf("on_clnt_write, name %s, ip %s, fd %d\n", info->name, info->ip, info->fd);
}


void on_clnt_newchk(int fd, chk_info *info) {
	/* not implement */
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
