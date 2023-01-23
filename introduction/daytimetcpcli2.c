#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>
#include <unp.h>

int main(int argc, char **argv) {

	int sockfd = 0, n = 0;
	char recv[MAXLINE + 1];
	struct sockaddr_in servaddr;

	if (2 != argc) {
		err_quit("Usage: ./a.out <ip-address>");
	}

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		err_sys("socket error");
	}

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(13);

	if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) < 0) {
		err_quit("inet_pton error for %s", argv[1]);
	}

	if (connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
		err_sys("connect error");
	}

	int counter = 0;
	while ((n = read(sockfd, recv, MAXLINE)) > 0) {
		++counter;
		recv[n] = 0;

		if (EOF == fputs(recv, stdout)) {
			err_quit("fputs error");
		}
	}
	fprintf(stdout, "stdout: %d\n", counter);
	if (n < 0) {
		err_sys("read error");
	}

	close(sockfd);
}
