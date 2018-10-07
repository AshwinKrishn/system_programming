#include <sys/mman.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(){

	int pid;
	char * shared_memory;
	shared_memory = mmap(NULL,1024 * sizeof(char),(PROT_WRITE | PROT_READ),(MAP_SHARED | MAP_ANONYMOUS),-1,0);
	pid = fork();
	if(pid >0){
		char ashwin[11] = "ashwinKrish";
		for(int i =0;i<11;i++){
			
			memcpy((shared_memory +i), &ashwin[i],1);  
			
		}		
		printf("written master\n");
	}
	else {

		for(int i = 0;i<11 ; i++){
			printf("string : %c\n", *(shared_memory +i));
		}
		printf("slave done \n");
	}
	munmap(shared_memory,1024*sizeof(char));
	return 0;
}
