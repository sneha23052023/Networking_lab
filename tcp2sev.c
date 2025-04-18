#//Matrix multiplication using TCP
include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

int main()
{
    int sfd,new_socket ,port,mt[4],a[10][10],b[10][10],c[10][10];
    struct sockaddr_in adress;
    char buffer[1024];
    socklen_t addr_len=sizeof(adress);
    printf("Enter the port number : ");
    scanf("%d",&port);

    sfd=socket(AF_INET , SOCK_STREAM, 0);

    adress.sin_family=AF_INET;
    adress.sin_addr.s_addr=INADDR_ANY;
    adress.sin_port= htons(port);
    bind(sfd ,(struct sockaddr*)&adress , sizeof(adress));

    listen(sfd,3);

    new_socket=accept(sfd, (struct sockaddr*)&adress , &addr_len);
    recv(new_socket ,&mt ,sizeof(mt),0);
    printf("received rows and columns");
    recv(new_socket ,&a ,sizeof(a),0);
    printf("\nreceived values for matrix 1");
    recv(new_socket ,&b ,sizeof(b),0);
    printf("\nreceived values for matrix 2");
     
    for(int i=0 ; i<mt[0];i++)
    {
        for(int j=0 ; j<mt[3];j++)
        {
            c[i][j]=0;
            for(int k=0; k<mt[1];k++)
            {
                c[i][j]=c[i][j]+a[i][k]*b[k][j];
            }
        }
    }
    send(new_socket,&c , sizeof(c) , 0);
    close(new_socket);
    close(sfd);
    

}