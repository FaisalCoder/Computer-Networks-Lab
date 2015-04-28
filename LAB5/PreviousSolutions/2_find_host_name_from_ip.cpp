#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>
int main(int argc, char *argv[])
{
    struct hostent *he;
    struct in_addr ipv4addr;

    inet_pton(AF_INET, argv[1], &ipv4addr);
    he = gethostbyaddr(&ipv4addr, sizeof ipv4addr, AF_INET);
    printf("Host name: %s\n", he->h_name);
}
