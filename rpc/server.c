<<<<<<< HEAD
#include "square.h"

square_out * prog_1_svc(square_in *in, struct svc_req *req) {
	static square_out out;
	out.res = in->arg * in->arg;
	return &out;
=======
#include "gfs_rpc.h"
#include <stdio.h>
#include <fcntl.h>

int *
gfs_open_1_svc(open_args *arg, struct svc_req *req) {
	static int fd;

	printf("path: %s\n", arg->path);
	if (arg->oflags & O_CREAT) {
		printf("O_CREAT\n");
	}
	fd = open(arg->path, arg->oflags, arg->mode);
	printf("open success\n");
	printf("fd: %d\n", fd);
	close(fd);

	return &fd;
>>>>>>> 7c1fbdb723e44449e80cbf2106290f40553cf043
}