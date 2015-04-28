#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define CHILDREN_NO 2

int main(void){

	int i,j;

	printf("Parent PID :%d\n",getpid());

    for( i=0;i<CHILDREN_NO;i++){

		 	pid_t pid = fork();

		 	if(pid==0){
		 		//CHILD PROCESS
		 		printf("Child PID %d\n",getpid());
		 		//sleep(2);

		 		for( j=0;j<CHILDREN_NO;j++){
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
		 scanf("%d",&s);
	return 0;
}
