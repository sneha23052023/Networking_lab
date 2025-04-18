//String reversal using TCP
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024

int main() {
    int sock = 0 ,PORT;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE] = {0};
    char input[BUFFER_SIZE];
   
    printf("Enter port number : ");
     scanf("%d",&PORT);
    
    
    printf("Enter a string: ");
    scanf("%s",input);

    // Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
   
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(PORT);
   

    // Connect to server
    connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    send(sock, input, strlen(input), 0);
    read(sock, buffer, BUFFER_SIZE);

    printf("Reversed from server: %s\n", buffer);

    close(sock);
    return 0;
}
