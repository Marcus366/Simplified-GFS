#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "gfs_fcntl.h"


int
main(int argc, char **argv) {
	int remote_fd;
	char buf[256];
	ssize_t nbytes;

	if (argc != 2) {
		fprintf(stderr, "usage: %s <MASTER IP>\n", argv[0]);
		exit(-1);
	}

	gfs_init(argv[1]);

	remote_fd = gfs_open("write_console_test", O_CREAT | O_RDWR, 0644);
	if (remote_fd <= 0) {
		fprintf(stderr, "open file error, fd:%d\n", local_fd);
		exit(-1);
	}

	while ((nbytes = read(stdin, buf, 256)) > 0) {
		gfs_write(remote_fd, buf, nbytes);
	}

	gfs_close(remote_fd);

	exit(0);
}