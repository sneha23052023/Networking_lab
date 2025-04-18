#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

int main()
{
    int sfd , port,a[10][10],b[10][10],c[10][10],mt[4];
    struct sockaddr_in servaddr, cliaddr;
    socklen_t addrlen=sizeof(servaddr);
    char buffer[1000];

    printf("Enter port number");
    scanf("%d",&port);

    sfd=socket(AF_INET, SOCK_DGRAM,0);

    servaddr.sin_family=AF_INET;
    servaddr.sin_addr.s_addr=INADDR_ANY;
    servaddr.sin_port=htons(port);

   printf("Enter rows and columns for matrix 1 and 2 : ");
   for(int i=0 ; i<4; i++)
    {
         scanf("%d",&mt[i]);
    }
    sendto(sfd,&mt , sizeof(mt),0,(struct sockaddr*)&servaddr , addrlen);

    printf("Enter matrix values of A : ");
    for(int i=0;i<mt[0];i++)
    {
        for(int j=0 ; j<mt[1]; j++)
        {
            scanf("%d",&a[i][j]);
        }
    }
    sendto(sfd,&a , sizeof(a),0,(struct sockaddr*)&servaddr , addrlen);

    printf("Enter matrix values of B : ");
    for(int i=0;i<mt[2];i++)
    {
        for(int j=0 ; j<mt[3]; j++)
        {
            scanf("%d",&b[i][j]);
        }
    }
    sendto(sfd,&b , sizeof(b),0,(struct sockaddr*)&servaddr , addrlen);

    recvfrom(sfd,&c , sizeof(c),0 ,(struct sockaddr*)&servaddr , &addrlen);

    for(int i=0;i<mt[0];i++)
    {
        for(int j=0 ; j<mt[3]; j++)
        {
            printf(" %d",c[i][j]);

        }
        printf("\n");
    }
    close(sfd);

}