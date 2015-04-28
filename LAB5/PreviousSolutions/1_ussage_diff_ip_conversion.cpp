#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>

int main(int argc, char *argv[])
{
    struct in_addr inp;
    memset(&inp, '\0', sizeof(inp));
    printf("Using inet_aton:\n");
    int retval = inet_aton(argv[1], &inp);
    if(retval)
    {
        printf("\tvalid ip - its hex rep<network byte order> = %x\n",inp.s_addr);
        printf("\tvalid ip - its hex rep<host byte order> = %x\n",ntohl(inp.s_addr));
        //printf("valid ip - its hex rep<host byte order> = %x\n",ntohl(inp.s_addr));
    }
    else
    {
        printf("\tinvalid ip\n");
    }

    memset(&inp, '\0', sizeof(inp));

    printf("\n\nUsing inet_addr:\n"); // not used as it gives -1 for error which is same as 255.25..
    inp.s_addr = inet_addr(argv[1]);
    if(inp.s_addr != -1)
    {
        printf("\treturn value not -1\n");
        printf("\tvalid ip - its hex rep<network byte order> = %x\n",inp.s_addr);
        printf("\tvalid ip - its hex rep<host byte order> = %x\n",ntohl(inp.s_addr));
    }
    else
        printf("\treturn value -1\n");

    memset(&inp, '\0', sizeof(inp));

    printf("\n\nUsing inet_network:\n");
    inp.s_addr = inet_network(argv[1]);
    if(inp.s_addr != -1)
    {
        printf("\treturn value not -1\n");
        printf("\tvalid ip - its hex rep<host byte order> = %x\n",inp.s_addr);
        printf("\tvalid ip - its hex rep<network byte order> = %x\n",htonl(inp.s_addr));
    }
    else
        printf("\treturn value -1\n");

    printf("\n\nUsing inet_ntoa:\n");

    inp.s_addr = htonl(inp.s_addr);
    printf("\tGetting back the string form: %s\n", inet_ntoa(inp));

    printf("\n\nUsing inet_lnaof and inet_netof:\n");
    unsigned int local_part, network_part;
    local_part = inet_lnaof(inp);
    network_part = inet_netof(inp);
    printf("\tlocal part: %x\n", local_part);
    printf("\tnetwork part: %x\n", network_part);

    printf("\n\nUsing inet_makeaddr to reconstruct the address from local and network part:\n");
    struct in_addr addr;
    addr = inet_makeaddr(network_part, local_part);
    printf("\taddress reconstructed: %x\n", ntohl(addr.s_addr));
}
