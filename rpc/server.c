#include "square.h"
#include <stdio.h>

square_out*
squareproc_1_svc(square_in *pin, struct svc_req *rqstp) {
	static square_out out;

	out.res1 = pin->arg1 * pin->arg1;
	fprintf(stdout, "input: %ld\n", pin->arg1);
	return (&out);
}