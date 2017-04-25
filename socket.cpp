#include "socket.h"
#include <sys/socket.h>
#include <sys/epoll.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>
#include <netdb.h>
#include <iostream>
#include <stdio.h>

using namespace aux_socket;

void finish(std::string message) {
	std::cerr << "ERROR IN " << message << "\n";
	perror(nullptr);
	exit(0);
}

int Socket(int domain, int type, int protocol) {
	int ret;
	if ((ret = socket(domain, type, protocol)) < 0) {
		finish("SOCKET");
	}
	return ret;
}

int Accept(int sockfd, sockaddr* addr, socklen_t* addrlen) {
	int ret;
	if ((ret = accept(sockfd, addr, addrlen)) < 0) {
		finish("ACCEPT");
	}
	return ret;
} 

int Accept4(int sockfd, sockaddr* addr, socklen_t* addrlen, int flags) {
	int ret;
	if ((ret = accept4(sockfd, addr, addrlen, flags)) < 0) {
		finish("ACCEPT4");
	}
	return ret;
}

int Listen(int sockfd, int backlog) {
	int ret;
	if ((ret = listen(sockfd, backlog)) < 0) {
		finish("LISTEN");
	}
	return ret;
}

int Bind(int sockfd, const sockaddr *addr, socklen_t addrlen) {
	int ret;
	if ((ret = bind(sockfd, addr, addrlen)) < 0) {
		finish("BIND");
	}
	return ret;
}

ssize_t Read(int fd, void* buf, size_t n) {
	int ret;
	if ((ret = read(fd, buf, n)) < 0) {
		if (errno == EAGAIN) {
			return -1;
		}
		finish("READ");
	}
	return ret;
}

ssize_t Write(int fd, const void* buf, size_t n) {
	int ret;
	if ((ret = write(fd, buf, n)) < 0) {
		finish("WRITE");
	}
	return ret;
}

int Epoll_create(int size) {
	int ret;
	if ((ret = epoll_create(size)) < 0) {
		finish("EPOLL CREATE");
	}
	return ret;
}

int Epoll_ctl(int epfd, int op, int fd, epoll_event* event) {
	int ret;
	if((ret = epoll_ctl(epfd, op, fd, event)) < 0) {
		finish("EPOLL CTL");
	}
	return ret;
}

int Epoll_wait(int epfd, epoll_event* events, int maxevents, int timeout) {
	int ret;
	if ((ret = epoll_wait(epfd, events, maxevents, timeout)) < 0) {
		finish("EPOLL WAIT");
	}
	return ret;
}

int Connect(int sockfd, sockaddr *addr, socklen_t addrlen) {
	int ret;
	if ((ret = connect(sockfd, addr, addrlen)) < 0) {
		finish("CONNECT");
	}
	return ret;
}