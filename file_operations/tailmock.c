#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>



void main(){

	int fd;
	char buff[100];
	fd = open("open_write_read.c",O_RDWR);	
	if(fd == -1){
		perror("OPEN ERRROR");
	}
	int err = lseek(fd,0,SEEK_END);
	
	if(err == -1){
		perror("OPEN ERRROR");
	}
	err = lseek(fd,-10,SEEK_CUR);
	err = read(fd,buff,10);	

	if(err == -1){
		perror("READ ERRROR");
	}
	buff[err] = '\0';
	printf("the last char is %s",buff);
	
}
