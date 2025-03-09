#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

int main() {
    int sockfd;
    struct sockaddr_in server_addr;

    // create a socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("socket");
        return 1;
    }

    // set up address struct
    memset(&server_addr, 0, sizeof(struct sockaddr_in));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = inet_addr("192.168.1.122");

    // connect to the server
    if (connect(sockfd, (struct sockaddr*) &server_addr, sizeof(struct sockaddr_in)) < 0) {
        perror("connect");
        return 1;
    }

    printf("Client successfully connected to the server.\n");

    // receive a message from the server
    char buffer[1024];
    int bytes_received = recv(sockfd, buffer, sizeof(buffer) - 1, 0);

    if (bytes_received < 0) {
        perror("recv");
        return 1;
    }

    // null-terminate the received data
    buffer[bytes_received] = '\0';
    printf("Message from the server: %s\n", buffer);

    // close socket
    close(sockfd);

    return 0;
}