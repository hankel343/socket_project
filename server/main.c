#include <sys/socket.h>		// socket functions
#include <netinet/in.h>		// address structs
#include <arpa/inet.h>		// common network conversion functions (i.e, inet_ntoa)
#include <unistd.h>		// POSIX API functions (e.g, close(), fork(), etc)
#include <string.h>
#include <stdio.h>

int main() {
	
	int sockfd;

	// create a socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0); // IPv4, TCP
	
	// set up address struct
	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(struct sockaddr_in));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8080);
	addr.sin_addr.s_addr = INADDR_ANY;

	// bind the socket to the address
	if (bind(sockfd, (struct sockaddr*)&addr, sizeof(struct sockaddr_in)) < 0) {
		perror("bind");
		return 1;
	}

	// listen for incoming connections
	if (listen(sockfd, 5) < 0) {
		perror("listen");
		return 1;
	}

	// accept incoming connections
	struct sockaddr_in client_addr;
	socklen_t client_addr_len = sizeof(struct sockaddr_in);
	int client_sockfd = accept(sockfd, (struct sockaddr*)&client_addr, &client_addr_len);

	if (client_sockfd < 0) {
		perror("accept");
		return 1;
	}

	printf("Connection accepted from ip address: %s\n", inet_ntoa(client_addr.sin_addr));

	// send a message to the client
	const char *message = "Hello from the server!";
	if (send(client_sockfd, message, strlen(message), 0) < 0) {
		perror("send");
		return 1;
	}
	
	// close client socket
	close(client_sockfd);

	// close server socket
	close(sockfd);

	return 0;
}
