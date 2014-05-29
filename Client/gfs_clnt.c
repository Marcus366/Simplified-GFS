#include "gfs_fcntl.h"
#include "gfs_rpc.h"
#include <fcntl.h>

CLIENT *mstr_clnt;
CLIENT *chk_clnt;

static int init_clnt(const char*);

int
main(int argc, char **argv) {
	int fd;

	if (argc != 3) {
		fprintf(stderr, "usage: %s <IP> <FILE PATH>", argv[0]);
		exit(-1);
	}

	if (init_clnt() == -1) {
		perror("clnt_create error");
		return -1;
	}
	
	fd = gfs_open(argv[2], O_CREAT | O_RDWR, 0);
	printf("open the file of fd: %d\n", fd);

	return (0);
}


int init_clnt(const char *ip) {
	mstr_clnt = clnt_create(argv[1], CLIENTPROG, VERSION, "tcp");
	if (mstr_clnt == NULL) {
		return -1;
	}
	return 0;
}