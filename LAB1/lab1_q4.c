#include<stdio.h>
#include <stdlib.h>
#include <string.h>

char message[100], crc_poly[100];

int clean()
{
    int l;
 //   printf("before checking clean val %s\n " , message);

    for(l=0; l<100; l++ )
    {
        if ( message[l] == '1')return l;
    }

    return -1;
}

int main()
{
    char message_copy[60];

    printf("Dataword : ");
    scanf("%s", &message_copy);

    printf("CRC polynomial : ");
    scanf("%s", &crc_poly);

    strcat(message, message_copy);
    char * message_copy2 = message;

    char zero = '0';
    char another[40];
    int y = 0;
    int nbit = strlen(crc_poly)-1;

    for( y; y < strlen(crc_poly)-1; y++)
    {
        another[y] = '0';
    }

    another[y] = '\0';

    strcat(message,another);




    int crclength = strlen(crc_poly);
    int l , i, dummy;

    do
    {

        l = clean();

        if ( l == -1 || ((strlen(message) - l) <= nbit )) break;

        for( i = 0; i < strlen(crc_poly); i++)
        {

        if ( message[l] == crc_poly[i] )
        {
            message[l] = '0';
        }

        else
        {
            message[l] = '1';
        }

        l++;
      }

      l = clean();
    }while(((strlen(message) - l) > nbit ));


     //extracting the remainder
     char result[100];
     strcpy(result,message_copy2);

     int i1 = strlen(message) - nbit  , m = 0;

     printf("CodeWord : %s", message_copy );

     while( m < nbit)
     {
         printf("%c", message[i1]);
         i1++;
         m++;
     }


   return 0;


}
