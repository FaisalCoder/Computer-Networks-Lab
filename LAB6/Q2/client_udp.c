#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <errno.h>

#define SERV_PORT 6767
#define MAXLEN 1000

int main(int argc, char ** arcv)
{
	int sockfd, type;
    char receiveline[MAXLEN];

	struct sockaddr_in serveraddr;
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	bzero(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(SERV_PORT);
	inet_pton(AF_INET, arcv[1], &serveraddr.sin_addr);
    
    int n;
    socklen_t len = sizeof(serveraddr);

    char sendline[] = "HELLO!!!";
    
    sendto(sockfd,sendline, strlen(sendline),0,(struct sockaddr *) &serveraddr, len);
    n = recvfrom(sockfd,receiveline,MAXLEN,0, NULL,NULL);
    receiveline[n] = 0;
    fputs(receiveline,stdout);

    //exit(0);
}