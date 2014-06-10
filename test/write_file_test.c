#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "gfs_fcntl.h"


int
main(int argc, char **argv) {
	int local_fd, remote_fd;
	char buf[256];
	ssize_t nbytes;

	if (argc != 2) {
		fprintf(stderr, "usage: %s <MASTER IP>\n", argv[0]);
		exit(-1);
	}

	local_fd = open("write_test", O_RDWR, 0644);
	if (local_fd <= 0) {
		fprintf(stderr, "open local file error, fd:%d\n", local_fd);
		exit(-1);
	}

	init(argv[1]);

	remote_fd = gfs_open("write_test", O_CREAT | O_RDWR, 0644);
	if (local_fd <= 0) {
		fprintf(stderr, "open file error, fd:%d\n", local_fd);
		exit(-1);
	}

	while ((nbytes = read(local_fd, buf, 256)) > 0) {
		gfs_write(remote_fd, buf, 256);
	}

	close(local_fd);
	gfs_close(remote_fd);

	exit(0);
}