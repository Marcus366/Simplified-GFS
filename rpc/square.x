struct square_in {
	int arg;
};

struct square_out {
	int res;
};

program PROGRAM {
	version VERSION {
		square_out PROG(square_in) = 1;
	} = 1;
} = 0x31330000;
