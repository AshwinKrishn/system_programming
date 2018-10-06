#include <stdio.h>
#include <setjmp.h>

jmp_buf excception;

void main(){

	int response;
	if(setjmp(excception)){
		printf("interrupt has occured critical error exiting");

	}
	else {
		printf("send me the code");
		scanf("%d",&response);
		if(response == 5){

			printf("you escaped \n :p \n");
		}
		else {
			longjmp(excception,1);
		} 
	}

}
