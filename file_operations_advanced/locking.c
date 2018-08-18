#include <stdio.h>
#include <error.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/file.h>
int main(int argv, char * argc[]){

	int fd_1,fd_2,temp;
	if(argv < 2){
		printf("Error : Usage ./hard_link file1 file2 ...\n");
		return -1;
	}		
	fd_1 = open(argc[1],O_RDWR);
	if(fd_1<0){
		perror("Error");
	}
	temp = flock(fd_1,LOCK_EX|LOCK_NB);
	if(temp < 0){
		perror("Error");
	}
	fd_2 = open(argc[1],O_RDWR);
	if(fd_2<0){
                perror("Error");
        }
	temp = flock(fd_2,LOCK_EX);
	if(temp < 0){
		perror("Error");
	}

}
