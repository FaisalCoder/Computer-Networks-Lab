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

#define SERV_PORT 6768
#define MAXLEN 1000
#define BACKLOG 5

int main(int argc, char ** arcv)
{
	int listenfd, connfd;
    char buff[MAXLEN];

    time_t ticks;
    pid_t pid;
    socklen_t len;
	struct sockaddr_in serveraddr, clientaddr;

	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	
	bzero(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(SERV_PORT);
	//inet_pton(AF_INET, arcv[1], &serveraddr.sin_addr);

	bind(listenfd, (struct sockaddr *) &serveraddr, sizeof(serveraddr));

	listen(listenfd, BACKLOG);

	for(;;)
		{
			len = sizeof(clientaddr);
			connfd = accept(listenfd, (struct sockaddr*) &clientaddr, &len);
			if((pid = fork()) ==0)
			{
				close(listenfd);
				ticks = time(NULL);
				snprintf(buff,sizeof(buff),"%.24s\r\n", ctime(&ticks));

				write(connfd, buff,strlen(buff));

				close(connfd);
				exit(0);
			}
			close(connfd);
			
		}
}