#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>

int main(){

	pid_t pid ; 
	pid = fork();

	if(pid > 0){
		sleep(1);
		printf("parent %d\n",getpid());
	}
	else if(pid == 0){
		printf("child %d,parent %d\n",getpid(),getppid());
	}


}

