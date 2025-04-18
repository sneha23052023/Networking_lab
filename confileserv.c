#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/wait.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void handle_request(int sockfd, struct sockaddr_in client_addr, char *filename) {
    char buffer[BUFFER_SIZE];
    FILE *fp = fopen(filename, "r");

    if (!fp) {
        snprintf(buffer, BUFFER_SIZE, "Error: File '%s' not found.\n", filename);
        sendto(sockfd, buffer, strlen(buffer), 0,
               (struct sockaddr *)&client_addr, sizeof(client_addr));
        return;
    }

    while (fgets(buffer, BUFFER_SIZE, fp)) {
        sendto(sockfd, buffer, strlen(buffer), 0,
               (struct sockaddr *)&client_addr, sizeof(client_addr));
        usleep(100000);  // simulate delay
    }

    strcpy(buffer, "__END__");
    sendto(sockfd, buffer, strlen(buffer), 0,
           (struct sockaddr *)&client_addr, sizeof(client_addr));

    fclose(fp);
    printf("Child %d: Sent file '%s' to %s:%d\n", getpid(), filename,
           inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
}

int main() {
    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);
    char buffer[BUFFER_SIZE];

    // Create UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Bind address
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("UDP File Server (fork version) listening on port %d...\n", PORT);

    while (1) {
        int n = recvfrom(sockfd, buffer, BUFFER_SIZE, 0,
                         (struct sockaddr *)&client_addr, &addr_len);
        if (n < 0) {
            perror("recvfrom failed");
            continue;
        }

        buffer[n] = '\0';  // Null-terminate the received data
        printf("Received file request '%s' from %s:%d\n",
               buffer, inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

        pid_t pid = fork();
        if (pid == 0) {
            // Child process
            handle_request(sockfd, client_addr, buffer);
            close(sockfd);
            exit(0);  // terminate child
        } else if (pid < 0) {
            perror("fork failed");
        }

        // Optionally clean up zombie processes
        while (waitpid(-1, NULL, WNOHANG) > 0);
    }

    close(sockfd);
    return 0;
}
