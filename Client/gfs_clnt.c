#include "gfs_fcntl.h"
#include "gfs_rpc.h"
#include <stdio.h>
#include <string.h>


CLIENT *mstr_clnt;

/*
int
main(int argc, char **argv) {
	int fd;
	char c, buf[256];

	if (argc != 2) {
		fprintf(stderr, "usage: %s <IP>\n", argv[0]);
		exit(-1);
	}

	if (init(argv[1]) == -1) {
		perror("clnt_create error");
		return -1;
	}

	while ((c = getchar())) {
		if (c == '\n') continue;
		switch(c) {
			case 'O':
				scanf("%s", buf);
				fd = gfs_open(buf, O_CREAT | O_RDWR, 0644);
				printf("open(O_CREAT) the file of fd: %d\n", fd);
				break;
			case 'o':
				scanf("%s", buf);
				fd = gfs_open(buf, O_RDWR, 0644);
				printf("open the file of fd: %d\n", fd);
				break;
			case 'c':
				scanf("%d", &fd);
				gfs_close(fd);
				break;
			case 'w':
				scanf("%s", buf);
				gfs_write(fd, buf, strlen(buf) + 1);
				printf("write fd(%d): %s\n", fd, buf);
				break;
			case 'r':
				while (gfs_read(fd, buf, 255) > 0) {
					printf("%s", buf);
				}
				break;
			default:
				printf("error input\n");
		}
	}
	return (0);
}*/


int gfs_init(const char *ip) {
	mstr_clnt = clnt_create(ip, CLNT_MSTR_PROG, VERSION, "tcp");
	if (mstr_clnt == NULL) {
		return -1;
	}
	return 0;
}