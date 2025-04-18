#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>


#define BUFFER_SIZE 1024

void reverse_string(char *str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char tmp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = tmp;
    }
}

int main() 
{
    int server_fd, new_socket,PORT;
    struct sockaddr_in address , cliaddr;
    char buffer[BUFFER_SIZE] = {0};
    socklen_t addrlen = sizeof(cliaddr);

    printf("Enter port number : ");
    scanf("%d",&PORT);

    // Creating socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }
   
    // Binding
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    bind(server_fd, (struct sockaddr *)&address, sizeof(address));

    // Listening
    listen(server_fd, 3);

    printf("Server listening on port %d...\n", PORT);

    // Accepting connection
    new_socket = accept(server_fd, (struct sockaddr *)&cliaddr, &addrlen);

    // Reading message
    read(new_socket, buffer, BUFFER_SIZE);
    printf("Received: %s\n", buffer);

    reverse_string(buffer);
    send(new_socket, buffer, strlen(buffer), 0);
    printf("Reversed string sent: %s\n", buffer);

    close(new_socket);
    close(server_fd);
    return 0;
}
