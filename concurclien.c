#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sockfd;
    char buffer[] = "TIME";
    struct sockaddr_in serv_addr;
    socklen_t addr_len = sizeof(serv_addr);
    time_t now;

    // Create UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

    // Send request
    sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&serv_addr, addr_len);

    // Receive response
    if (recvfrom(sockfd, &now, sizeof(now), 0, (struct sockaddr *)&serv_addr, &addr_len) < 0) {
        perror("recvfrom failed");
        close(sockfd);
        return 1;
    }

    printf("Server time: %s", ctime(&now));

    close(sockfd);
    return 0;
}
