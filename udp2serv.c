//Matrix multiplication using UDP
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

int main()
{
    int sfd , port,a[10][10],b[10][10],c[10][10],mt[4];
    struct sockaddr_in servaddr, cliaddr;
    socklen_t addrlen=sizeof(cliaddr);
    char buffer[1000];

    printf("Enter port number");
    scanf("%d",&port);

    sfd=socket(AF_INET, SOCK_DGRAM,0);

    servaddr.sin_family=AF_INET;
    servaddr.sin_addr.s_addr=INADDR_ANY;
    servaddr.sin_port=htons(port);

    bind(sfd,(const struct sockaddr * )&servaddr , sizeof(servaddr));

    recvfrom(sfd,&mt , sizeof(mt),0 ,(struct sockaddr*)&cliaddr , &addrlen);
    recvfrom(sfd,&a , sizeof(a),0,(struct sockaddr*)&cliaddr , &addrlen);
    recvfrom(sfd,&b , sizeof(b),0,(struct sockaddr*)&cliaddr , &addrlen);

    for(int i=0;i<mt[0];i++)
    {
        for(int j=0 ; j<mt[3]; j++)
        {
            c[i][j]=0;
            for(int k=0 ; k<mt[1] ; k++)
            {
                c[i][j]+=a[i][k]*b[k][j];
            }
        }
    }
    sendto(sfd,&c , sizeof(c),0,(struct sockaddr*)&cliaddr , addrlen);
    close(sfd);

}