// socket wrapper functions

#include "unp.h"
#include <asm-generic/errno.h>
#include <stdlib.h>
#include <sys/socket.h>

// include Socket
int Socket(int family, int type, int protocol) {
	int n = 0;
	if ((n = socket(family, type, protocol)) < 0) {
		err_sys("sockatmark error");
	}

	return (n);
}

void Bind(int fd, const struct sockaddr *sa, socklen_t slen) {
	if (bind(fd, sa, slen) < 0) {
		err_sys("bind_error");
	}
}

void Listen(int fd, int backlog) {
	char *ptr;

	if ((ptr = getenv("LISTENQ")) != NULL) {
		backlog = atoi(ptr);
	}

	if (listen(fd, backlog) < 0) {
		err_sys("listen error");
	}
}

int Accept(int fd, struct sockaddr *sa, socklen_t *slenptr) {
	int n = 0;

again:
	if ((n = accept(fd, sa, slenptr)) < 0) {
#ifdef EPROTO
		if (EPROTO == errno || ECONNABORTED == errno)
#else
		if (errno == ECONNABORTED)
#endif
			goto again;
		else
			err_sys("accept error");
	}

	return (n);
}
