#ifndef SOCKET_H
#define SOCKET_H

#include <sys/socket.h>
#include <sys/epoll.h>
#include <netdb.h>
#include <iostream>

namespace aux_socket {
	
	void finish(std::string message);

	int Socket(int domain, int type, int protocol);
	int Accept(int sockfd, sockaddr* addr, socklen_t* addrlen);
	int Accept4(int sockfd, sockaddr* addr, socklen_t* addrlen, int flags);
	int Listen(int sockfd, int backlog);
	int Bind(int sockfd, const sockaddr *addr, socklen_t addrlen);
	
	int Epoll_create(int size);
	int Epoll_ctl(int epfd, int op, int fd, epoll_event* event);
	int Epoll_wait(int epfd, epoll_event* events, int maxevents, int timeout);

	ssize_t Read(int fd, void* buf, size_t n);
	ssize_t Write(int fd, const void* buf, size_t n);

	int Connect(int sockfd, sockaddr *addr, socklen_t addrlen)
}

#endif