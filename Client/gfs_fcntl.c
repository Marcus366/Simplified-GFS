#include "gfs_rpc.h"
#include "gfs_clnt.h"
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <stddef.h>


int gfs_open(const char *path, int oflags, mode_t mode) {
	int *pfd;
	open_args arg;

	arg.oflags = oflags;
	arg.mode =  mode;
	arg.path = (char*)malloc(strlen(path) + 1);
	strcpy(arg.path, path);

	pfd = ask_mstr_open_1(&arg, mstr_clnt);

	free(arg.path);

	if (pfd == NULL) {
		fprintf(stderr, "fd NULL error\n");
		return -1;
	}
	printf("open file of fd(%d)\n", *pfd);

	return (*pfd);
}


int gfs_close(int fd) {
	int *pfd;
	close_args arg;

	arg.fd = fd;
	pfd = ask_mstr_close_1(&arg, mstr_clnt);

	if (pfd == NULL) {
		fprintf(stderr, "fd NULL error");
		return -1;
	}
	printf("close result: %d\n", *pfd);

	return (*pfd);
}


ssize_t gfs_read(int fd, void *buf, size_t count) {
	CLIENT *chk_cl;
	chk_info *pinfo;
	read_args args;
	read_res *res;

	args.fd = fd;
	args.count = count;
	pinfo = ask_mstr_read_1(&args, mstr_clnt);
	if (pinfo == NULL) {
		fprintf(stderr, "ask_mstr_read return NULL\n");
		exit(-1);
	}

repeat:	//printf("gfs_read, chk_info: %s %s %d\n", pinfo->name, pinfo->ip, pinfo->fd);
	chk_cl = clnt_create(pinfo->ip, CLNT_CHK_PROG, VERSION, "tcp");
	if (chk_cl == NULL) {
		fprintf(stderr, "gfs_read, clnt_create failed\n");
		exit(-1);
	}

	args.fd = pinfo->fd;
	res = ask_chk_read_1(&args, chk_cl);
	if (res == NULL) {
		fprintf(stderr, "gfs_read, ask_chk_read failed\n");
		exit(-1);
	}
	if (res->ssize > 0) {
		memcpy(buf, res->buf, res->ssize);
	} else {
		pinfo = ask_mstr_nextchk_1(&fd, mstr_clnt);
		if (pinfo == NULL) {
			fprintf(stderr, "ask_mstr_nextchk return NULL\n");
			exit(-1);
		}
		if (pinfo->fd != -1 && count - res->ssize > 0) {
			buf += res->ssize;
			count -= res->ssize;

			args.fd = pinfo->fd;
			args.count = count;

			clnt_destroy(chk_cl);
			goto repeat;
		}
	}
	clnt_destroy(chk_cl);
	return (ssize_t)res->ssize;
}


ssize_t gfs_write(int fd, const void *buf, size_t nbytes) {
	int *res;
	CLIENT *chk_cl;
	chk_info *pinfo;
	write_args args;

	args.fd = fd;
	args.nbytes = nbytes;
	args.buf = (char*)malloc(nbytes);
	memcpy(args.buf, buf, nbytes);
	pinfo = ask_mstr_write_1(&args, mstr_clnt);
	if (pinfo == NULL) {
		fprintf(stderr, "ask_mstr_write return NULL\n");
		exit(-1);
	}

	printf("gfs_write, chk_info: %s %s %d\n", pinfo->name, pinfo->ip, pinfo->fd);
	chk_cl = clnt_create(pinfo->ip, CLNT_CHK_PROG, VERSION, "tcp");
	if (chk_cl == NULL) {
		fprintf(stderr, "gfs_write, clnt_create failed\n");
		exit(-1);
	}
	args.fd = pinfo->fd;

repeat:
	res = ask_chk_write_1(&args, chk_cl);

	if (res == NULL) {
		fprintf(stderr, "ask_chk_write_1 return NULL");
		free(args.buf);
		exit(-1);
	}
	printf("gfs_write %u bytes, but actually %d bytes\n", nbytes, *res);
	if (*res < nbytes) {
		buf 	= buf + *res;
		nbytes 	= nbytes - *res;
		pinfo = ask_mstr_newchk_1(&fd, mstr_clnt);
		if (pinfo == NULL) {
			fprintf(stderr, "ask_mstr_write return NULL\n");
			exit(-1);
		}
		args.fd = pinfo->fd;
		args.nbytes = nbytes;
		strcpy(args.buf, buf);

		clnt_destroy(chk_cl);
		chk_cl = clnt_create(pinfo->ip, CLNT_CHK_PROG, VERSION, "tcp");
		goto repeat;
	}
	clnt_destroy(chk_cl);
	return (ssize_t)*res;
}
