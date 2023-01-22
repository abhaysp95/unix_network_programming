#include <asm-generic/errno.h>
#include <bits/types/time_t.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>
#include <unp.h>

int main(int argc, char **argv) {
	int listenfd = 0, connfd = 0;
	struct sockaddr_in servaddr;
	char buff[MAXLINE];
	time_t ticks;

	// listenfd = Socket(AF_INET, SOCK_STREAM, 0);
	if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		err_sys("socket error");
	}

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(13);  // daytime server
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	// Bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
	if (bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
		err_sys("bind error");
	}

	// Listen(listenfd, LISTENQ);
	char *ptr;
	int backlog = 0;
	if ((ptr = getenv("LISTENQ")) != NULL) {
		backlog = atoi(ptr);
	}
	if (listen(listenfd, backlog) < 0) {
		err_sys("listen error");
	}

	while (1) {
		// connfd = Accept(listenfd, (struct sockaddr *)NULL, NULL);
		while ((connfd = accept(listenfd, (struct sockaddr *)NULL, NULL)) < 0) {
#ifdef EPROTO
			if (EPROTO == errno || ECONNABORTED == errno) {
#else
			if (ECONNABORTED == errno) {
#endif
				continue;
			} else {
				err_sys("accept error");
			}
		}

		ticks = time(NULL);
		snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
		// Write(connfd, buff, strlen(buff));
		if (write(connfd, buff, strlen(buff)) != strlen(buff)) {
			err_sys("write error");
		}

		// Close(connfd);
		if (close(connfd) < 0) {
			err_sys("conn close error");
		}
	}
}
