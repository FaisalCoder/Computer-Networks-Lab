#include<stdlib.h>
#include<string.h>

void stuffing(char * a)
{
    char d[100];
    int i=0, j=0, count, k =0;

    for( i; i < strlen(a); i++)
    {

        d[k++] = a[i];
k
        if ( a[i] == '0')
        {

            j= i+1;
            count = 0;
            for(j; j<strlen(a);j++)
            {

                if ( a[j] == '1')
                {
                    i = j;
                    d[k++] = a[j];
                    count++;

                   if ( count == 5)
                   {
                       //pattern found add a 0
                       d[k++] = '0';

                       break;
                   }
                }

                else
                {
                    i = j-1;
                    break;
                }
            }
        }
    }
    d[k] = '\0';
    printf("Bit stuffed data : %s", d);

}

void destuff( char * a)
{
    char d[100];
    int i=0, j=0, count, k =0;

    for( i; i < strlen(a); i++)
    {

        d[k++] = a[i];

        if ( a[i] == '0')
        {

            j= i+1;
            count = 0;
            for(j; j<strlen(a);j++)
            {

                if ( a[j] == '1')
                {
                    i = j;
                    d[k++] = a[j];
                    count++;

                   if ( count == 5)
                   {
                       if ( (j+1 < strlen(a) && (a[j+1] == '0')))
                       {
                           i++;
                           break;

                       }
                       //pattern found add a 0
                   }
                }

                else
                {
                    i = j-1;
                    break;
                }
            }
        }
    }
    d[k] = '\0';
    printf("De-stuffed data : %s", d);


}


int main()
{
    char data[100];
    char stuff[100];
    printf("Enter the data to be sent : ");
    scanf("%s",&data);
    stuffing(data);

    printf("\n\nEnter the data to be received : ");
    scanf("%s",&stuff);
    destuff(stuff);

    return 0;
}
