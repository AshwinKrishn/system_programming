#include <stdio.h>
#include <error.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

void main(){

	int fd;
	off_t offset;
	char ashwin[100];
	struct stat  ff;
	fd = open("Makefile",S_IRUSR|S_IWUSR);
	if(fd == -1){
		perror("reason open failed :");
	}
	lseek(fd,4,SEEK_SET);	
	int readed = read(fd,ashwin,20);
	if(readed == -1){
		perror("reason read failed :");
	}
	ashwin[readed] = '\0';
	printf("the string is\" %s\" \n\n number readed %d\n",ashwin,readed);
}	
