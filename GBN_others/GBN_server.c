#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>

struct Packet {

    int mInfo;
    int mAck;
    int mType;
}mProduced, Ack;

int main(int argc, char *argv[])
{
    int listenfd = 0, connfd = 0;
    int i=0,j,k;
    struct sockaddr_in serv_addr;
    int lastsent = 0;
    int recack[1000];
    int lastack = -1;
    char sendBuff[1025];
    time_t ticks;

    for(j =0;j<1000;j++)
    recack[j] = 0;
	
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(sendBuff, '0', sizeof(sendBuff));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(4444);

    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
		printf("server started !!\n");
    listen(listenfd, 10);

    while(1)
    {
        connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);
    while(1) {
        mProduced.mType=0;
        mProduced.mInfo = lastsent;
        printf("Packet no. %d is being sent.\n", mProduced.mInfo);
        write(connfd,(void*)&mProduced, sizeof(mProduced));
        if((i = read(connfd,(void*)&Ack,sizeof(Ack))) > 0) {
            if(Ack.mInfo!=-1){
                lastack = Ack.mInfo;
                for(k=0;k<lastack;k++)
                    recack[k] = 1;
                printf("Acknowlegment of packet %d received\n", Ack.mInfo);
            }
        }
        if(lastsent-3 >= 0)
            if(!recack[lastsent-3])
                lastsent = lastsent-4;
            sleep(1);
        lastsent++;
    }
    close(connfd);
     }
}
