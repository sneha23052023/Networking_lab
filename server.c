#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>

int main()
{
    int sfd , newsocket , port;
    char buffer[1000], fileread[100];
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
    bind(sfd , (struct sockaddr *)&servaddr , sizeof(servaddr));

    printf("\n Binding succesful");

    listen(sfd,5);
    printf("\nListening...");

    newsocket=accept(sfd , (struct sockaddr *)&cliaddr, &addrlen);
    printf("\nConnection established");

    int n=recv(newsocket ,buffer , sizeof(buffer)-1 , 0);
    buffer[n]='\0';
    fp=fopen(buffer , "r");
    printf("\nFile recieved : %s",buffer);
    if(fp==NULL)
    {
        send(newsocket , "error" , strlen("error"), 0);
        close(newsocket);
            exit(1);

    }

    while(fgets(fileread , sizeof(fileread) , fp))
    {
        if(send(newsocket , fileread , strlen(fileread), 0)< 0)
        {
            close(sfd);
            close(newsocket);
            fclose(fp);
            exit(1);
        }

    }
    
    send(newsocket , "completed" , strlen("completed"), 0);
    fclose(fp);
    close(sfd);
    close(newsocket);
}