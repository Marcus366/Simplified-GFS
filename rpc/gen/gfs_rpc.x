struct open_args {
	string path<>;
	int oflags;
	u_int mode;
};

struct close_args {
	int fd;
};

struct read_args {
	int fd;
	char *buf;
	long count;
};

struct write_args {
	int fd;
	char *buf;
	long nbytes;
};

program CLNT_MSTR_PROG {
	version VERSION {
		int ask_mstr_open(open_args) 	= 1;
		int ask_mstr_close(close_args) 	= 2;
		long ask_mstr_read(read_args) 	= 3;
		long ask_mstr_write(write_args) 	= 4;
	} = 1;
} = 0x31230000;

program MSTR_CHK_PROG {
	version VERSION {
		int ask_chk_open(open_args) 	= 1;
		int ask_chk_close(close_args) 	= 2;
	} = 1;
} = 0x31230001;
