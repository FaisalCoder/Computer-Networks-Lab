#include <sys/types.h>
#include <sys/socket.h>
#include <cstdio>
#include <cstdlib>

int main()
{
    int socket_TCP_fd;
    socket_TCP_fd = socket(AF_INET, SOCK_STREAM, 0);

    if(socket_TCP_fd == -1)
    {
        printf("ERROR opening socket tcp\n");
    }

    int socket_UDP_fd;
    socket_UDP_fd = socket(AF_INET, SOCK_DGRAM, 0);

    if(socket_UDP_fd == -1)
    {
        printf("ERROR opening socket udp\n");
    }

    int value;
    unsigned int value_len;
    socklen_t optlen;
    printf("TCP: Default send buffer length:\n");
    if(getsockopt(socket_TCP_fd, SOL_SOCKET, SO_SNDBUF, &value, &value_len) == 0)
    {
        printf("\tsend buffer size:%d\n",value);
        printf("\tsizeof(this):%d\n",value_len);
    }

    printf("TCP: Default recieve buffer length:\n");
    if(getsockopt(socket_TCP_fd, SOL_SOCKET, SO_RCVBUF, &value, &value_len) == 0)
    {
        printf("\trcv buffer size:%d\n",value);
        printf("\tsizeof(this):%d\n",value_len);
    }

    printf("\nUDP: Default send buffer length:\n");
    if(getsockopt(socket_UDP_fd, SOL_SOCKET, SO_SNDBUF, &value, &value_len) == 0)
    {
        printf("\tsend buffer size:%d\n",value);
        printf("\tsizeof(this):%d\n",value_len);
    }

    printf("UDP: Default recieve buffer length:\n");
    if(getsockopt(socket_UDP_fd, SOL_SOCKET, SO_RCVBUF, &value, &value_len) == 0)
    {
        printf("\trcv buffer size:%d\n",value);
        printf("\tsizeof(this):%d\n",value_len);
    }

    printf("\nChanging tcp rcv buffer size\n");

    int temp_size;
    printf("\tEnter new size:");
    scanf("%d",&temp_size);

    if(setsockopt(socket_TCP_fd, SOL_SOCKET, SO_RCVBUF, &temp_size, sizeof(temp_size)) == 0)
        printf("Set successfull\n");
    else
        printf("Set Fail\n");

    printf("New TCP recieve buffer length:\n");
    if(getsockopt(socket_TCP_fd, SOL_SOCKET, SO_RCVBUF, &value, &value_len) == 0)
    {
        printf("\trcv buffer size:%d\n",value);
        printf("\tsizeof(this):%d\n",value_len);
    }

    printf("New TCP send buffer length:\n");
    if(getsockopt(socket_TCP_fd, SOL_SOCKET, SO_SNDBUF, &value, &value_len) == 0)
    {
        printf("\tsend buffer size:%d\n",value);
        printf("\tsizeof(this):%d\n",value_len);
    }
}
