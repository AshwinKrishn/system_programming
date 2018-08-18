#include <stdio.h>
#include <error.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argv,char * argc[]){

	int temp;
	if(argv < 2){
		printf("Error : Usage ./hard_link file1 file2 ...\n");
		return -1;
	}		
	unlink("hard_sample.txt");	
	temp = link(argc[1],"hard_sample.txt");
	
	if(temp <0){
		perror("Error while creating hard link");
	}
	temp = unlink (argc[1]);
	if(temp <0){
		perror("Error while unlinking\n");
	}
	
	

}
