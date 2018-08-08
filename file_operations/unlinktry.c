
#include <stdio.h>
#include <error.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

void main(){

	int result;
	result = unlink("trylseek");
	if(result == -1){
		perror("deletion failed");
	}
	
}
