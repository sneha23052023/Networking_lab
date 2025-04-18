//Matrix multiplication using TCP
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

int main()
{
    int sock,new_socket ,port,mt[4],a[10][10],b[10][10],c[10][10];
    struct sockaddr_in adress;
    char buffer[1024];
    socklen_t addr_len=sizeof(adress);

    printf("Enter the port number : ");
    scanf("%d",&port);

    sock=socket(AF_INET , SOCK_STREAM, 0);

    adress.sin_family=AF_INET;
    adress.sin_addr.s_addr=INADDR_ANY;
    adress.sin_port= htons(port);
   
    connect(sock,(struct sockaddr*)&adress , sizeof(adress));

    printf("Enter rows and columns for matrix 1 ");
    scanf("%d%d",&mt[0],&mt[1]);
    printf("Enter rows and columns for matrix 2 ");
    scanf("%d%d",&mt[2],&mt[3]);

    send(sock,&mt ,sizeof(mt),0);
    printf("enter value for 1st matrix : ");
    for(int i=0 ; i<mt[0];i++)
    {
        for(int j=0 ; j<mt[1];j++)
        {
            scanf("%d",&a[i][j]);
        }
    }
    send(sock,&a ,sizeof(a),0);
    printf("enter value for 2nd matrix : ");
    for(int i=0 ; i<mt[2];i++)
    {
        for(int j=0 ; j<mt[3];j++)
        {
            scanf("%d",&b[i][j]);
        }
    }
    send(sock,&b ,sizeof(b),0);

    recv(sock, &c , sizeof(c),0);
    printf("product is : \n");
    for(int i=0 ; i<mt[0];i++)
    {
        for(int j=0 ; j<mt[3];j++)
        {
            printf("%d ",c[i][j]);
        }
        printf("\n");
    }

    
    close(sock);
    

}