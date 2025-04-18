//Multiple client and single server communication using TCP
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

#define PORT 6666

int main()
{
    int sockfd, newsocket;
    struct sockaddr_in serveraddr,cliaddr;
    socklen_t addr_size=sizeof(cliaddr);
    char buffer[1024];
    pid_t childpid;
    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        printf("\n Socket creation error \n");
        exit(1);
    }

    printf("socket is created \n");

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(PORT);
    serveraddr.sin_addr.s_addr = INADDR_ANY;

    bind(sockfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr));  

    printf("Binding successful \n");
    listen(sockfd, 6);
    printf("listening...\n");

    while (1) 
    {
        newsocket = accept(sockfd, (struct sockaddr*)&cliaddr, &addr_size);
        if (newsocket < 0) 
        {
            exit(1);
        }
        printf("\nconnection accepted from %s:%d\n", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));

       if ((childpid = fork()) == 0)
     
         {
            close(sockfd);
            while (1) 
            {
                recv(newsocket, buffer, 1024, 0);
                if (strcmp(buffer, "exit") == 0) 
                {
                    printf("Disconnected from %s:%d\n", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));
                    break;
                }

                printf("Client [%s:%d] sent: %s\n", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port), buffer);
                send(newsocket, buffer, strlen(buffer), 0);
               // bzero(buffer, sizeof(buffer));
            }
        }
    }

    return 0;
}