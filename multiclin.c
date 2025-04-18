//Multiple client and single server communication using TCP
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

#define PORT 6666

int main()
{
    int clientsocket;
    struct sockaddr_in serveraddr;
    char buffer[1024];

    clientsocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientsocket < 0) {
        perror("socket failed \n");
        exit(EXIT_FAILURE);
    }

    printf("socket created successfully \n");

    //memset(&serveraddr, '\0', sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serveraddr.sin_port = htons(PORT);

    connect(clientsocket, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
    
    printf("connected to server \n");

    while (1) 
    {
        printf("enter a message : \t");
        scanf("%s", buffer);
        send(clientsocket, buffer, strlen(buffer), 0);

        if (strcmp(buffer, "exit") == 0) {
            close(clientsocket);
            printf("disconnected from server \n");
            exit(1);
        }

        if (recv(clientsocket, buffer, 1024, 0) < 0) 
            printf("error in receiving data \n");
         else 
            printf("server: %s\n", buffer);
        
    }

    return 0;
}