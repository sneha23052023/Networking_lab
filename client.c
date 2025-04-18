#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>

int main()
{
    int sfd , newsocket , port;
    char buffer[1000], fileread[100],name[100],fname[100];
    struct sockaddr_in servaddr , cliaddr;
    socklen_t addrlen =sizeof(servaddr);
    FILE *fp;

    printf("Enter port number : ");
    scanf("%d",&port);

    sfd=socket(AF_INET , SOCK_STREAM ,0);
    printf("\n Socket created");

    servaddr.sin_family=AF_INET;
    servaddr.sin_addr.s_addr=INADDR_ANY;
    servaddr.sin_port=htons(port);
    connect(sfd , (struct sockaddr *)&servaddr , sizeof(servaddr));

    printf("Connection established");

    printf("\n Enter file name : ");
    scanf("%s",name);
    send(sfd,name , strlen(name),0);
    printf("\n Enter file name to change : ");
    scanf("%s",fname);
    fp=fopen(fname , "w");
    if(fp==NULL)
    {
        close(sfd);
        exit(1);
    }
    while(1)
    {
        int n=recv(sfd,buffer , sizeof(buffer)-1, 0);
        if(n<0)
        break;
        buffer[n]='\0';

        if(strcmp(buffer,"completed")==0 || strcmp(buffer,"error")==0)
        {
            break;
        }
        fprintf(fp ,"%s",buffer);
    }

    fclose(fp);

    close(sfd);
}