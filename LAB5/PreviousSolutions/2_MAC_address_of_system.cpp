#include <sys/socket.h>
#include <sys/ioctl.h>
#include <linux/if.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>

int main()
{
    struct ifreq s;
    int fd = socket(AF_INET, SOCK_STREAM, 0);

    strcpy(s.ifr_name, "eth0");
    if (ioctl(fd, SIOCGIFHWADDR, &s) == 0)
    {
        for (int i = 0; i < 5; ++i)
            printf("%02x:", (unsigned char) s.ifr_addr.sa_data[i]);
        printf("%02x", (unsigned char) s.ifr_addr.sa_data[5]);
        printf("\n");
    }
}
