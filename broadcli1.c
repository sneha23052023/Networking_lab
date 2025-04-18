#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>


void main()
{
  int clientsocket,port1;
  char str[20];
  struct sockaddr_in serveraddr,clientaddr;
  socklen_t  len=sizeof(serveraddr);

  clientsocket=socket(AF_INET,SOCK_DGRAM,0);
  printf("Socket created successfully\n");

  //memset(&serveraddr,0,sizeof(serveraddr));
  //memset(&clientaddr,0,sizeof(clientaddr));
  
  clientaddr.sin_family= AF_INET;
  serveraddr.sin_addr.s_addr= INADDR_ANY;
  clientaddr.sin_port= htons(4000);

  bind(clientsocket,(struct sockaddr*)&clientaddr,sizeof(clientaddr));
  printf("Binding successfull\n");


  printf("Enter the port number");
  scanf("%d",&port1);

  serveraddr.sin_family= AF_INET;
  serveraddr.sin_addr.s_addr= inet_addr("127.0.0.1");
  serveraddr.sin_port = htons(port1);

  recvfrom(clientsocket,&str,sizeof(str),0,(struct sockaddr*)&serveraddr,&len);
  printf("message from server is %s",str);

}

