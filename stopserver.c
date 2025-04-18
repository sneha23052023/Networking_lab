//Stop and Wait Protocol
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
typedef struct packet {
    char data[1024];
} packet;

typedef struct frame {
    int frame_kind; // ACK: 0, SEQ: 1, FIN: 2
    int seq_no;
    int ack;
    packet packet;
} frame;

void main() 
{
    int sockfd, frame_id = 0;
    struct sockaddr_in serveraddr;
    char buffer[1024];
    socklen_t addr_size = sizeof(serveraddr);
    frame frame_send, frame_recv;
    
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(6666);
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    bind(sockfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr));

    while(1) 
    {
        int n = recvfrom(sockfd, &frame_recv, sizeof(frame), 0,(struct sockaddr*)&serveraddr, &addr_size);

        if (n > 0 && frame_recv.frame_kind == 1 && frame_recv.seq_no == frame_id) {
            printf("\n[+]Frame Received: %s\n", frame_recv.packet.data);
            frame_send.seq_no = 0;
            frame_send.frame_kind = 0;
            frame_send.ack = frame_recv.seq_no + 1;

            sendto(sockfd, &frame_send, sizeof(frame), 0,(struct sockaddr*)&serveraddr, addr_size);
            printf("[+]Ack Sent\n");
        } else 
        {
            printf("[-]Frame not received\n");
        }

        frame_id++;
    }

    close(sockfd);
}