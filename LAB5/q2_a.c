#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <arpa/inet.h>
int main(int argc, char **argv)
{
    struct hostent *hp; 
    char *ip;
    in_addr_t data; 
    struct hostent *he;
    struct sockaddr_in ipv4addr;
    struct in6_addr ipv6addr;

    if (argc = 2) {
    ip = argv[1];
    data = inet_addr(ip);
    hp = gethostbyaddr(&data, 4, AF_INET);
   
    if (hp == NULL) {
    printf("Unknown host\n");
    exit(1);
    }
    else {
    printf("Host name: %s\n", hp->h_name);
    printf("\n");
    }
    }
    else printf("argv error");
    return 0;
}
