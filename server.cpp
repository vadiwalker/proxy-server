#include <sys/types.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
#include <iostream>
#include "socket.h"

#define PORT 8080
#define BUFSZ 1024

using namespace aux_socket;

char buf[BUFSZ];

struct handler_t {

	handler_t(int socket) 
		: socket(socket) {}

	int socket;
	char buffer[BUFSZ];
};

int main() {
	int sockfd = Socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);

	sockaddr_in addr;
	bzero(&addr, sizeof(addr));

	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htons(INADDR_ANY);
	addr.sin_port = htons(PORT);

	Bind(sockfd, (sockaddr *) &addr, sizeof(addr));
	Listen(sockfd, 100000);
		
	int epoll_fd = Epoll_create(10);
	epoll_event event;
	event.events = EPOLLIN;
	event.data.ptr = new handler_t(sockfd);
	
	Epoll_ctl(epoll_fd, EPOLL_CTL_ADD, sockfd, &event);
	epoll_event *events = (epoll_event*) calloc(64, sizeof event);
	
	while (true) {
		
		int n = Epoll_wait(epoll_fd, events, 64, -1);
		for (int i = 0; i < n; i++) {
				
			handler_t* handler = (handler_t*) events[i].data.ptr;
			int socket = handler -> socket;

			if (socket == sockfd) {

				int infd = Accept4(sockfd, (sockaddr*) nullptr, nullptr, SOCK_NONBLOCK);
				
				event.data.ptr = new handler_t(infd);
				event.events = EPOLLIN | EPOLLOUT;
				
				Epoll_ctl(epoll_fd, EPOLL_CTL_ADD, infd, &event);

			} else {

				handler_t* handler = (handler_t*) events[i].data.ptr;
						
				bzero(handler -> buffer, sizeof(handler -> buffer));
				if (Read(handler -> socket, handler -> buffer, BUFSZ) > 0) { 
					Write(handler -> socket, handler -> buffer, BUFSZ);
				}
			}
		}
	}
		


	return 0;
}
