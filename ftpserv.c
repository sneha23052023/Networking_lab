// File tranfer using TCP
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

int main()
{
    int sfd , newsocket ,port;
    struct sockaddr_in servaddr , cliaddr;
    char buffer[1000],fileread[100];
    int addrlen=sizeof(cliaddr);
    FILE *fp;
    printf("\nEnter port number : ");
    scanf("%d",&port);
    sfd=socket(AF_INET , SOCK_STREAM , 0);
    printf("\n socket created....");
    servaddr.sin_family=AF_INET;
    servaddr.sin_addr.s_addr=INADDR_ANY;
    servaddr.sin_port=htons(port);
    bind(sfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    listen(sfd,5);
    printf("\nlistening....");
    newsocket = accept(sfd ,(struct sockaddr *)&cliaddr,&addrlen);
    if (newsocket < 0) {
        perror("\nAccept failed");
        exit(1);
    }
    printf("\nConnection accepted...");
    int n=recv(newsocket , buffer , 1000 ,0);
    buffer[n]='\0';
    printf("\nfile name recieved : %s\n",buffer);

    fp=fopen(buffer,"r");
    
    if(fp == NULL)
    {
        send(newsocket,"error", strlen("error"), 0);
        close(newsocket);
        close(sfd);
        return 1;  // exit the server gracefully
    }
    
    while(fgets(fileread, sizeof(fileread),fp))
    { 

        if(send(newsocket ,fileread, strlen(fileread),0)<0)
        {
            fclose(fp);
            close(newsocket);
    close(sfd);

        }
    }
    fclose(fp);
    send(newsocket,"completed" ,strlen("completed"), 0);
    close(newsocket);
    close(sfd);
}