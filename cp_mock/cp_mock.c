#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <error.h>
#include <errno.h>

extern int errno;

int fd_src, fd_dest,written;
void check_fd(int fd, void (* handle)(void)){
	
	if(fd<0){
		perror("error encountered");
	
		if(handle == NULL){
			exit(0);
		}
		else{
			handle();
		}
	}
}

void main(int argv ,const char *argc []){

	char source[255] , destination[255],buff[255] ;
	if(argv != 3){
		printf("Usage ./cp_strcpy source destination\n");
		exit(0);
	}
	
	snprintf(source,strlen(argc[1])+1,"%s\n",argc[1]);
	fd_src = open(source,O_RDONLY);
	check_fd(fd_src,NULL);
	
	snprintf(destination,strlen(argc[2])+1,"%s\n",argc[2]);
	fd_dest = open(destination, O_RDWR | O_CREAT );
	check_fd(fd_dest,NULL);	
	lseek(fd_dest,0,SEEK_END);
	chmod(destination,S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
	check_fd(fd_dest,NULL);

	do{
		written = 0 ;
		written = read(fd_src,buff,1);
		check_fd(written,NULL);
		
		if(written > 0) { 
			written = write(fd_dest,buff,1);
			check_fd(written,NULL);
		}
	}while(written != 0);	
}
