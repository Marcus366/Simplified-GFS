#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "gfs_fcntl.h"


int
main(int argc, char **argv) {
	int fd;
	char buf[256];
	ssize_t nbytes;

	if (argc != 2) {
		fprintf(stderr, "usage: %s <MASTER IP>\n", argv[0]);
		exit(-1);
	}

	init(argv[1]);

	fd = gfs_open("write_test", O_CREAT | O_RDWR, 0644);
	if (fd <= 0) {
		fprintf(stderr, "open file error, fd:%d\n", fd);
		exit(-1);
	}

	while ((nbytes = gfs_read(fd, buf, 256)) > 0) {
		write(1, buf, nbytes);
	}

	gfs_close(fd);

	exit(0);
}