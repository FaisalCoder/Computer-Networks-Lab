#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    struct in_addr addr;

   if (argc != 2) {
        fprintf(stderr, "%s <enter dotted-address>\n", argv[0]);
        return 0;
    }

   if (inet_aton(argv[1], &addr) == 0) {
        fprintf(stderr, "Invalid address\n");
        return 0;
    }

   printf("%s\n", inet_ntoa(addr));
   return 0;
}
