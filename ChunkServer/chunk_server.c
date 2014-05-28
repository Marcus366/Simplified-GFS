#include "gfs.h"


/**
 * Here is Chunk_Server start up code
 * on start up, chunk server connect to master,
 * tell him "I am want to join the cluster" and send port number to him
 * then chunk server run loop to wait for client
 */


static void start_up(const char *master_addr, in_port_t serv_port);


int
main(int argc, char **argv) {
	if (argc != 2) {
		perror("usage: ChunkServer [IP for MasterServer]");
	}


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
	serv_addr.sin_port = htons(0);

	if (bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) {
		perror("bind error");
	}

	if (listen(listenfd, LISTEN_BACKLOG) == -1) {
		perror("listen error");
	}

	start_up(argv[1], serv_addr.sin_port);

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
			strcpy(buf, "chunk server want to suck your dick");
			write(connfd, buf, strlen(buf));
			/*			test end				*/

			exit(0);
		}
		close(connfd);
	}
	exit(0);
}


void start_up(const char *master_addr, in_port_t serv_port) {
	int sockfd;
	char buf[256];
	struct sockaddr_in servaddr;

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket error");
	}
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(MASTER_PORT);
	inet_pton(AF_INET, master_addr, &servaddr.sin_addr);

	if (connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == -1) {
		perror("connect error");
	}
	
	sprintf(buf, "CHUNK HERE %u", serv_port);
	printf("%s\n", buf);
	if (write(sockfd, buf, strlen(buf)) < 0) {
		perror("write error");
	}
	close(sockfd);
}