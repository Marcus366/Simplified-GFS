#include "gfs.h"

int
main(int argc, char **argv) {
	int sockfd;
	struct sockaddr_in servaddr;

	if (argc != 2) {
		perror("usage: Client [IP for MasterServer]");
	}

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket error");
	}
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(MASTER_PORT);
	inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

	if (connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == -1) {
		perror("connect error");
	}

	/********** test below **************/
	char buf[255];
	int nread;
	if ((nread = read(sockfd, buf, 255)) > 0) {
		buf[nread] = 0;
		printf("%s\n", buf);
	}
	/*			test end				*/

	exit(0);
}