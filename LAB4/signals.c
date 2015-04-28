#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define CHILD_COUNT 2

int main(void){

	int i,j;

	printf("Parent PID :%d\n",getpid());

    for( i=0;i<CHILD_COUNT;i++){

		 	pid_t pid = fork();

		 	if(pid==0){
		 		//CHILD PROCESS
		 		printf("Child PID %d\n",getpid());
		 		//sleep(2);

		 		for( j=0;j<CHILD_COUNT;j++){
		 			pid_t pidc = fork();
		 			if(pidc ==0){
		 				//GRANDCHILD PROCESS
		 				printf("Grand child PID %d\n",getpid() );
		 				break;
		 			}
		 		}
		 		break;
		 	}
		 }

		 int s;
		 sleep(2);
		// scanf("%d",&s);
	return 0;
}
