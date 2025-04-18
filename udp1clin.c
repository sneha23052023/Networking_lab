#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024

int main() {
    int sockfd,PORT;
    char buffer[BUFFER_SIZE];
    char input[BUFFER_SIZE];
    struct sockaddr_in serv_addr;
    socklen_t addr_len = sizeof(serv_addr);

    printf("Enter port number : ");
    scanf("%d",&PORT);

    printf("Enter a string: ");
    scanf("%s",input);

    // Create UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = INADDR_ANY; // or use inet_pton for a remote IP

    // Send message
    sendto(sockfd, input, strlen(input), 0, (const struct sockaddr *)&serv_addr, sizeof(serv_addr));

    // Receive response
    recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&serv_addr, &addr_len);
    buffer[strlen(buffer)] = '\0';

    printf("Reversed from server: %s\n", buffer);

    close(sockfd);
    return 0;
}
