#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

void main()
{
  int serversocket,port,cliport=4000;
  char str[20];
  struct sockaddr_in serveraddr,clientaddr1;

  serversocket=socket(AF_INET,SOCK_DGRAM,0);
  printf("Socket created successfully");

 
 // memset(&serveraddr,0,sizeof(serveraddr));
  //memset(&clientaddr1,0,sizeof(clientaddr1));
 
  printf("Enter the port number");
  scanf("%d",&port);
  serveraddr.sin_family= AF_INET;
  serveraddr.sin_addr.s_addr= INADDR_ANY;
  serveraddr.sin_port= htons(port);
  bind(serversocket,(struct sockaddr *)&serveraddr,sizeof(serveraddr));
  printf("binding successfull\n");

  printf("Enter the string\n");
  scanf("%s",str);

  while(cliport<4004)
{
  clientaddr1.sin_family=AF_INET;
  clientaddr1.sin_addr.s_addr= INADDR_ANY;
  clientaddr1.sin_port=htons(cliport);
  sendto(serversocket,&str,sizeof(str),0,(struct sockaddr *)&clientaddr1,sizeof(clientaddr1));
  cliport++;
  
 }
close(serversocket);


 }
