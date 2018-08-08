#include <stdio.h>
#include <error.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

void main(){

	int fd;
	creat("ashwin.txt",O_RDWR |S_IRUSR|S_IWUSR|S_IXUSR);
	fd = open("ashwin.txt",O_RDWR);
	if(fd == -1){
		perror("ERRROR");
	}
	chmod("ashwin.txt",S_IRUSR | S_IWUSR |S_IXUSR );
	if(fd == -1){
		perror("ERRROR");
	}
	close(fd);
}
