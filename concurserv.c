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
    char buffer[BUFFER_SIZE];
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);

    // Create UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind the socket
    if (bind(sockfd, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("UDP Time Server listening on port %d...\n", PORT);

    while (1) {
        
        // Wait for client request
        int n = recvfrom(sockfd, buffer, BUFFER_SIZE , 0, (struct sockaddr *)&client_addr, &addr_len);
        buffer[n] = '\0'; // Null-terminate to be safe

        printf("Received request '%s' from %s:%d\n", buffer, inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

        // Handle TIME request
        if (strcmp(buffer, "TIME") == 0) 
        {
            time_t now = time(NULL);

            // Print the time on server
            printf("Sending current time: %s", ctime(&now));

            // Send the time back to client
            sendto(sockfd,&now, sizeof(now), 0,(struct sockaddr *)&client_addr, addr_len);
        }
    }

    close(sockfd);
    return 0;
}
