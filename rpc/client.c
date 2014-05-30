<<<<<<< HEAD
#include "square.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char **argv) {
	CLIENT *cl;
	square_out *out;
	square_in  *in;

	char *server = argv[1];
	in->arg = atoi(argv[2]);

	cl = clnt_create(server, PROGRAM, VERSION, "tcp");
	out = prog_1(in, cl);

	printf("%d\n", out->res);

	return 0;
}
=======
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
>>>>>>> 7c1fbdb723e44449e80cbf2106290f40553cf043
