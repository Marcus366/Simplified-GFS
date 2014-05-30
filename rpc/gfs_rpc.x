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

program CLIENTPROG {
	version VERSION {
		int ask_mstr_open(open_args) 	= 1;
		int ask_gfs_close(close_args) 	= 2;
		long gfs_read(read_args) 	= 3;
		long gfs_write(write_args) 	= 4;
	} = 1;
} = 0x31230000;
