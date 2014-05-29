#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include "gfs_rpc.h"

int
main(int argc, char **argv) {
	CLIENT *cl;
	open_args arg;
	int *fd;

	if ((cl = clnt_create(argv[1], CLIENTPROG, VERSION, "tcp")) == NULL) {
		perror("clnt_create error");
		return -1;
	}
	arg.oflags =  O_RDWR | O_CREAT;
	arg.mode =  0xf0000000;
	arg.path = (char*)malloc(strlen(argv[2] + 1));
	strcpy(arg.path, argv[2]);

	fd = gfs_open_1(&arg, cl);
	if (fd == NULL) {
		fprintf(stderr, "%s error", argv[1]);
		return -1;
	}
	printf("result: %d\n", *fd);

	return 0;
}
