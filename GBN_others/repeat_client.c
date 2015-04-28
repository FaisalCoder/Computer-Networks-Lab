#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>

#define MAX_SIZE 4


struct Packet {
    int mInfo;
    int mAck;
    int mType;
}mReceived,Ack;


int main(int argc, char *argv[])
{
    char i;
    int sockfd = 0, n = 0, rb = 0, start=0;
    struct Packet recvBuff[4];
    int rec[8]={0};
    struct sockaddr_in serv_addr;
    int to_be_received = 0;
    int lastack = -1,j=0,k=0,t=0,flag = 0,h;


    if(argc != 2)
    {
        printf("\nServer IP not given\n");
        return 1;
    }

    memset(recvBuff, '0',sizeof(recvBuff));
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Error : Could not create socket \n");
        return 1;
    }

    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(5000);

    if(inet_pton(AF_INET, argv[1], &serv_addr.sin_addr)<=0)
    {
        printf("\n inet_pton error occured\n");
        return 1;
    }

    if( connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
       printf("\n Error : Connect Failed \n");
       return 1;
    }

    while (1)
    {
    if((n = read(sockfd, &mReceived, sizeof(mReceived))) < 0)
        break;
    int in;
    printf("start=%d k=%d tobe=%d\n", start,k,to_be_received);
    printf("Packet %d arrived.\n 1. Receive?\n 2. Reject\n",mReceived.mInfo);
    scanf("%d",&in);
    if(in==1) {

        if(mReceived.mInfo != to_be_received) {
            flag = 0;
            if(mReceived.mInfo<start+MAX_SIZE && mReceived.mInfo>=start) {
                for(t = 0; t<4;t++)
                 {
                    if(rec[t]==1 && (mReceived.mInfo==recvBuff[t].mInfo))            // Check If packet is already present
                        flag = 1;
                }
                if(!flag) {
                    printf("Packet %d buffered\n",mReceived.mInfo);
                    recvBuff[k++] = mReceived;
                    rec[mReceived.mInfo]=1;
                    Ack.mInfo = mReceived.mInfo;                                //Store the packet
                    Ack.mType = 2;
                    write(sockfd, (void*)&Ack, sizeof(Ack));
                }
                else {
                    printf("Duplicate packet %d dropped\n", mReceived.mInfo);
                    Ack.mInfo = mReceived.mInfo;
                    Ack.mType = 3;                                                  // Duplicate packet received
                    write(sockfd, (void*)&Ack, sizeof(Ack));
                }
            } else {
                printf("Packet %d dropped\n",mReceived.mInfo);
                Ack.mInfo = to_be_received;                                //Packet outside the window received and discarded
                Ack.mType = 3;
                write(sockfd, (void*)&Ack, sizeof(Ack));
            }
        } else {
            recvBuff[0] = mReceived;
            printf("%d\n",mReceived.mInfo);
            rec[mReceived.mInfo]=1;
                  rb=0;                       // Required packet received

                while(rec[start]==1)
                    {
                        //printf("K=%d\n",k);

                        printf("%d sent to Network Layer!\n",recvBuff[rb].mInfo);
                        rec[start]=0;
                      //  printf("TOBE=%d\n", start);
                      lastack=rb;
                        rb=(rb+1)%4;
                        start=(start+1)%8;
                    }
                k=0;

            Ack.mInfo = to_be_received;
            Ack.mType = 1;
            write(sockfd,(void*)&Ack, sizeof(Ack));
            lastack = to_be_received;
            to_be_received=((recvBuff[lastack].mInfo)+1)%8;

        }
    }
    else {
        k=(k+1)%4;
        Ack.mInfo = to_be_received;
        Ack.mType = 3;
        write(sockfd,(void*)&Ack, sizeof(Ack));
        }
    for(h=0;h<4;h++)
        printf("%d ", recvBuff[h].mInfo);
        printf("\n");

    }

    if(n < 0)
    {
        printf("\n Read error \n");
    }
    return 0;
}
