#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

void errorMsg(char* msg)
{
    printf("\n%s\n", msg);
//  exit(0);
}

void sort(int input[], int length) {
    int i, j;
    for (i = 0; i < (length - 1); i++) {
        for (j = 0; j < length - i - 1; j++) {
            if (input[j] > input[j + 1]) {
                int temp = input[j];
                input[j] = input[j + 1];
                input[j + 1] = temp;
            }
        }
    }
}


// move this into global space and make it const (non modifiable, easyer to debug)
const char text_to_send[] = "Anything that you want will not be considered no matter what you do!! Haha";

int main()
{
    int servfd[2];
    int clntfd[2];
    int chldpid;    

    if(pipe(servfd) < 0)
        errorMsg("Unable to create server pipe.!!");
    if(pipe(clntfd) < 0)
        errorMsg("Unable to create client pipe.!!!");

    if((chldpid = fork()) == 0)
    {
        close(servfd[1]);
        close(clntfd[0]);

        int n;

        //Input
        int numberOfInputs;
	    printf("CLIENT : Enter number of inputs to sort: ");
	    scanf("%d", &numberOfInputs);
	    write(clntfd[1], &numberOfInputs, sizeof (numberOfInputs));
	    printf("CLIENT : Enter numbers to sort:\n");
	    int i;
	    for (i = 0; i < numberOfInputs; i++) {
	        int num;
	        scanf("%d", &num);
	        int success = write(clntfd[1], &num, sizeof (num));
	        if (success == -1) {
	            printf("CLIENT : Error: %s\n", strerror(errno));
	            return -1;
	        }
	    }

	    //read from server
	    printf("CLIENT : Sorted array: ");
	    for (i = 0; i < numberOfInputs; i++) {
	        int output;
	        int success = read(servfd[0], &output, sizeof (output));
	        if (success == -1) {
	            printf("CLIENT : Error: %s\n", strerror(errno));
	            return -1;
	        }
	        printf("%d ", output);
	    }
	    printf("\n");

        // this is not nessesary at this point, but it is good style to clean up after yourself
        close(servfd[0]);
        close(clntfd[1]);
    }

    else    
    {
        //printf("Parent:   \n\n");
        close(servfd[0]);
        close(clntfd[1]);
        char txt[256]; // same here, you need to actually allocate a buffer.
        int success;  
        //read from user
        int numberOfInputs;
	    read(clntfd[0], &numberOfInputs, sizeof (numberOfInputs));
	    printf("SERVER : %d input numbers received : ", numberOfInputs);

	    int input[numberOfInputs];
	    int i;
	    for (i = 0; i < numberOfInputs; i++) {
	        int num;
	        success = read(clntfd[0], &num, sizeof (num));
	        if (success == -1) {
	            printf("Error: %s\n", strerror(errno));
	            return -1;
	        }
	        printf("%d ", num);
	        input[i] = num;
	    }
	    printf("\n");
	    sort(input, numberOfInputs);
	    for (i = 0; i < numberOfInputs; i++) {
	        int toWrite = input[i];
	        success = write(servfd[1], &toWrite, sizeof (toWrite));
	        if (success == -1) {
	            printf("SERVER : Error: %s\n", strerror(errno));
	            return -1;
	        }
	    }
	    
        // close the loose file descriptors, else your child will read on them forever
        close(servfd[1]);
        close(clntfd[0]);

        int status;
        wait(&status); // this is called like this. if you want to use the pid you call waitpid(chldpid, &status, 0);
    }
    exit(0);            
}
