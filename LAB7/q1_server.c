#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

#define MAXLINE 4096 /*max text line length*/
#define SERV_PORT 3000 /*port*/
#define LISTENQ 8 /*maximum number of client connections */

#define true 1
#define false 0

int palindrome (char * word)
{
    int start_index = 0;
    int end_index = strlen(word) - 2;
   // printf("start : %d \nend : %d \n", start_index , end_index );

    int i = 0;
    for( i ; i < strlen(word)-1; i++ )
    {
  //  printf("start : %c\nend : %c\n" , word[start_index], word[end_index]);
         if ( word[start_index] != word[end_index] )
         {
      //      printf("false");
              return false;
         }

         start_index++;
         end_index--;
    }


    return true;
}

int main (int argc, char **argv)
{
    int listenfd, connfd, n, len = 0;
    socklen_t clilen;
    char buf[MAXLINE];
    struct sockaddr_in cliaddr, servaddr;

//creation of the socket
    listenfd = socket (AF_INET, SOCK_STREAM, 0);

//preparation of the socket address
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);

    bind (listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

    listen (listenfd, LISTENQ);

    printf("%s\n","Server running...waiting for connections.");

    for ( ; ; )
    {

        clilen = sizeof(cliaddr);
        connfd = accept (listenfd, (struct sockaddr *) &cliaddr, &clilen);
        printf("%s\n","Received request...");

        while ( (n = recv(connfd, buf, MAXLINE,0)) > 0)
        {
            printf("%s","String received from and resent to the client:");
            puts(buf);
            buf[n] = '\0';
            int result = palindrome(buf);
            char end[] = {'s','t','o','p','\0'};


            if( (strlen(buf)-1) == 4){
              if ( buf[0] == 's' && buf[1] == 't' && buf[2] == 'o' && buf[3] == 'p' ){

                //printf("stopped...");
                send(connfd, end, sizeof(end), 0);
                close(connfd);
                close (listenfd);
                exit(1);
              }

            }


            char no[] = "Not a palindrome";
            char yes[] = "Palindrome";

            if ( result == false){
                send(connfd, no, sizeof(no), 0);
            }

            else{
               send(connfd, yes, sizeof(yes), 0);
            }
          //  send(connfd, buf, n, 0);
        }



        if (n < 0)
        {
            perror("Read error");
            exit(1);
        }
        close(connfd);

    }
//close listening socket
    close (listenfd);
}
