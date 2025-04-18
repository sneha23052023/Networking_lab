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
    char buffer[1000],fileread[100],name[10],fname[10];
    socklen_t addr_len=sizeof(cliaddr);
    FILE *fp;
    printf("\nEnter port number : ");
    scanf("%d",&port);
    sfd=socket(AF_INET , SOCK_STREAM , 0);
    printf("\nsocket created...");
    servaddr.sin_family=AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port=htons(port);
    if (connect(sfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
        perror("\nConnect failed");
        exit(1);
    }
    printf("\nConnection established...");
    printf("\nEnter file name: ");
    scanf("%s",name);
    send(sfd,name ,strlen(name), 0);

    printf("\nEnter file name to be written into: ");
    scanf("%s",fname);
    
    fp=fopen(fname,"w");
    
    while (1)
    {
        int n = recv(sfd, buffer, sizeof(buffer)-1, 0);
        if (n <= 0)
            break;
    
        buffer[n] = '\0';
    
        if (strcmp(buffer, "completed") == 0 || strcmp(buffer, "error") == 0)
            break;
    
        fprintf(fp, "%s", buffer);
    }
    
    fclose(fp);
    close(sfd);
}