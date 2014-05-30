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
