#include <stdio.h>
#include "square.h"

int
main(int argc, char **argv) {
	CLIENT *cl;
	square_in in;
	square_out *pout;

	if ((cl = clnt_create(argv[1], SQUARE_PROG, SQUARE_VER, "tcp")) == NULL) {
		perror("clnt_create error");
		return -1;
	}
	in.arg1 = atol(argv[2]);

	pout = squareproc_1(&in, cl);
	if (pout == NULL) {
		fprintf(stderr, "%s error", argv[1]);
		return -1;
	}
	printf("result: %ld\n", pout->res1);

	return 0;
}