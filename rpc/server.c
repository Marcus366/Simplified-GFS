#include "square.h"

square_out * prog_1_svc(square_in *in, struct svc_req *req) {
	static square_out out;
	out.res = in->arg * in->arg;
	return &out;
}