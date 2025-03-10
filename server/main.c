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

	printf("Server is running and waiting for connections...\n");

	for (;;) {
		// accept incoming connections
		struct sockaddr_in client_addr;
		socklen_t client_addr_len = sizeof(struct sockaddr_in);
		int client_sockfd = accept(sockfd, (struct sockaddr*)&client_addr, &client_addr_len);

		if (client_sockfd < 0) {
			perror("accept");
			return 1;
		}

		printf("Connection accepted from ip address: %s\n", inet_ntoa(client_addr.sin_addr));

		pid_t pid = fork();
		if (pid < 0) {
			perror("fork");
			close(client_sockfd);
			continue;
		}

		if (pid == 0) {
			close(sockfd);

			char command[256];
			int bytes_received = recv(client_sockfd, command, sizeof(command) - 1, 0);
			
			if (bytes_received < 0) {
				perror("recv");
				close(client_sockfd);
				return 1;
			}

			command[bytes_received] = '\0';

			// execute command and capture output
			FILE *fp = popen(command, "r");
			if (fp == NULL) {
				perror("popen");
				close(client_sockfd);
				_exit(1);
			}

			// read output from command
			char buffer[1024];
			ssize_t bytes_read;
			ssize_t total_bytes_sent = 0;
			while ((bytes_read = fread(buffer, 1, sizeof(buffer), fp)) > 0) {
				if (send(client_sockfd, buffer, bytes_read, 0) < 0) {
					perror("send");
					break;
				}
				total_bytes_sent += bytes_read;
			}

			printf("Total %zd bytes sent to client.\n", total_bytes_sent);
			pclose(fp);
			close(client_sockfd);
			_exit(0);

		} else {

			// Parent process: close the client socket and continue to accept new connections
			close(client_sockfd);

		}

		// receive the command from the client
		char command[256];
		int bytes_received = recv(client_sockfd, command, sizeof(command) - 1, 0);
		if (bytes_received < 0) {
			perror("recv");
			close(client_sockfd);
			continue;
		}
		command[bytes_received] = '\0';

		// execute the top command and capture its output
		FILE *fp = popen(command, "r");
		if (fp == NULL) {
			perror("popen");
			close(client_sockfd);
			continue;
		}

		// read the output from the top command
		char buffer[1024];
		size_t bytes_read;
		size_t total_bytes_sent = 0;
		while ((bytes_read = fread(buffer, 1, sizeof(buffer), fp)) > 0) {
			
			// send the output to the client
			if (send(client_sockfd, buffer, bytes_read, 0) < 0) {
				perror("send");
				break;
			}
			total_bytes_sent += bytes_read;
		}
		
		printf("Total %zu bytes sent to client.\n", total_bytes_sent);
		// close the popen file descriptor
		pclose(fp);

		// close client socket
		close(client_sockfd);
	}

	// close server socket
	close(sockfd);

	return 0;
}
