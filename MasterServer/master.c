#include "gfs.h"

/**
 * Here is the MasterServer startup code.
 * Master is responsible for the
 * 1. file management:
 * 		such as keep up the message about 
 * 		filename(full path name) mapping to the chunk location
 * 		(it is easy to use a tree to keep up )
 * 2. intereact with client
 * 
 */

int
main(int argc, char **argv) {
	int listenfd, connfd;
	pid_t child_pid;
	socklen_t cli_len;
	struct sockaddr_in cli_addr, serv_addr;

	if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket error");
	}

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(MASTER_PORT);

	if (bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) {
		perror("bind error");
	}

	if (listen(listenfd, LISTEN_BACKLOG) == -1) {
		perror("listen error");
	}


	while (1) {
		cli_len = sizeof(cli_addr);
		if ((connfd = accept(listenfd, (struct sockaddr*)&cli_addr, &cli_len)) == -1) {
			perror("accept error");
		}
		printf("%d connected\n", cli_addr.sin_addr.s_addr);
		if ((child_pid = fork()) == 0) {
			close(listenfd);
			/********** test below **************/
			char buf[255];
			strcpy(buf, "connect succeed");
			write(connfd, buf, strlen(buf));
			/*			test end				*/

			exit(0);
		}
		close(connfd);
	}
	exit(0);
}
