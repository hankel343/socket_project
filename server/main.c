#include <sys/socket.h>		// socket functions
#include <netinet/in.h>		// address structs
#include <arpa/inet.h>		// common network conversion functions (i.e, inet_ntoa)
#include <unistd.h>		// POSIX API functions (e.g, close(), fork(), etc)
#include <string.h>
#include <stdio.h>

int main(int argc, char** argv) {
	
	int sockfd;

	// create a socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0); // IPv4, TCP
	
	// set up address struct
	struct addrinfo addr;

	memset(&addr, 0, sizeof(struct addrinfo));

// 	status = getsockopt(sockfd, SOL_SOCKET, SO_SNDBUF, &optval, &optlen);
// 
// 	if ( status != 0 ) {
// 		perror("getsockopt");
// 		return 1;
// 	}

	return 0;
}
