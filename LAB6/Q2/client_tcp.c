#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <errno.h>

#define SERV_PORT 6768
#define MAXLEN 1000

int main(int argc, char ** arcv)
{
	int sockfd, type;
    char receiveline[MAXLEN];

	struct sockaddr_in serveraddr;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	bzero(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(SERV_PORT);
	inet_pton(AF_INET, arcv[1], &serveraddr.sin_addr);

	if( connect(sockfd, (struct sockaddr *) & serveraddr, sizeof(serveraddr)) < 0)
        printf("Error1 !!!\n");
    
    int n;
    while( (n = read(sockfd, receiveline, MAXLEN)) > 0)
    {
        receiveline[n]=0;
        if(fputs(receiveline, stdout) == EOF)
            printf("Error !!! \n");
    }

	exit(0);
}