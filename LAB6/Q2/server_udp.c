#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>

#define SERV_PORT 6767
#define MAXLEN 1000
#define BACKLOG 5

int main(int argc, char ** arcv)
{
	int listenfd;
    char buff[MAXLEN],sendline[MAXLEN];

    time_t ticks;
    pid_t pid;
    socklen_t len;
	struct sockaddr_in serveraddr, clientaddr;

	listenfd = socket(AF_INET, SOCK_DGRAM, 0);
	
	bzero(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(SERV_PORT);
	
	bind(listenfd, (struct sockaddr *) &serveraddr, sizeof(serveraddr));

	int n;
	for(;;)
		{
			len = sizeof(clientaddr);
			n = recvfrom(listenfd, buff, MAXLEN, 0, (struct sockaddr*) &clientaddr, &len);

			ticks = time(NULL);
			snprintf(sendline,sizeof(sendline),"%.24s\r\n", ctime(&ticks));
			sendto(listenfd,sendline,strlen(sendline),0,(struct sockaddr*) &clientaddr, len);
		}
}