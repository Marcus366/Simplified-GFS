#include "gfs_rpc.h"
#include "gfs_clnt.h"
#include <string.h>
#include <sys/types.h>
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
	/* not implement */
	//static ssize_t *psize;
	return 0;
}


ssize_t gfs_write(int fd, const void *buf, size_t nbytes) {
	int *psize;
	write_args arg;

	arg.fd = fd;
	arg.nbytes = nbytes;
	arg.buf = malloc(nbytes);
	memcpy(arg.buf, buf, nbytes);

	psize = ask_mstr_write_1(&arg, mstr_clnt);

	if (psize == NULL) {
		fprintf(stderr, "write return NULL");
		return -1;
	}

	return (ssize_t)(*psize);
}
