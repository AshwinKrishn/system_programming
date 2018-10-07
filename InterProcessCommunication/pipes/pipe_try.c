#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main (){

	int pid;

	if(mkfifo("commfifo",0777) != 0){

		perror("pipe creation failed");
	}
	pid = fork();

	if(pid > 0){
		int fd;
		char buffer[128];
		printf("I am master I will write data\n");
		fd = open("commfifo",O_WRONLY);
		for(int i = 0;i<10;i++){
			sprintf(buffer,"wrote %d",i);
			write(fd,buffer,sizeof("wrote 1"));
			memset(buffer,'\0',128);
			
		}
		write(fd,"END",sizeof("END"));
		printf("I am master I finished writing data\n");
		close(fd);
		wait(NULL);
	}
	else {

		int fd ;
		printf("slave I will read\n");
		fd = open("commfifo",O_RDONLY);
		char buffer[128];
		for(int i = 0;i<12;i++){
			read(fd,buffer,sizeof("wrote 1"));
			printf("%s\n",buffer);
			
			if(strcmp(buffer,"END") == 0){
				printf("found the end of the file\n");
				break;
				}
			memset(buffer,'\0',128);
			}
		close(fd);
	}
	unlink("commfifo");	

	return 0;
}
