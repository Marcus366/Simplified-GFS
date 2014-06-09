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
	unsigned int count;
};

struct read_res {
	int ssize;
	char *buf;
};

struct write_args {
	int fd;
	char *buf;
	unsigned int nbytes;
};

struct chk_info {
	string name<>;
	string ip<>;
	int fd;	
};

program CLNT_MSTR_PROG {
	version VERSION {
		int ask_mstr_open(open_args)		= 1;
		int ask_mstr_close(close_args)		= 2;
		chk_info ask_mstr_read(read_args)	= 3;
		chk_info ask_mstr_write(write_args)	= 4;
		chk_info ask_mstr_newchk(int)		= 5;
		chk_info ask_mstr_nextchk(int)		= 6;
	} = 1;
} = 0x31230000;

program MSTR_CHK_PROG {
	version VERSION {
		int ask_chk_open(open_args)	= 1;
		int ask_chk_close(close_args)	= 2;
	} = 1;
} = 0x31230001;

program CHK_MSTR_PROG {
	version VERSION {
		int reg_chk(string)	= 1;
		int unreg_chk(string)	= 2;
	} = 1;
} = 0x31230002;

program CLNT_CHK_PROG {
	version VERSION {
		int ask_chk_write(write_args)		= 1;
		read_res ask_chk_read(read_args)	= 2;
	} = 1;
} = 0x31230003;
