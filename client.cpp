#include <iostream>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <errno.h>
#include <netdb.h>
#include <fcntl.h>
#include "socket.h"

#define PORT 8080
#define BUFSZ 1024

using namespace aux_socket;

int main() {
	int sockfd;
	char* send = new char[BUFSZ];
	char* recv = new char[BUFSZ];

	sockaddr_in addr;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	bzero(&addr, sizeof(addr));

	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);

	inet_pton(AF_INET, "127.0.0.1", &(addr.sin_addr));

	Connect(sockfd, (sockaddr*) &addr, sizeof(addr));

	while (1) {
		bzero(send, BUFSZ);
		bzero(recv, BUFSZ);
		fgets(send, BUFSZ, stdin);
		write(sockfd, send, strlen(send)+1);
		read(sockfd, recv, BUFSZ);
		fputs(recv, stdout);
	}
	return 0;
}
			