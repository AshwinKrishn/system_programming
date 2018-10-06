#include <dirent.h>
#include <stdio.h>
#include <error.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int ls_mock(char * filepath){

	DIR * dir;
	struct dirent * direc_entry;
	dir = opendir(filepath);
	if(!dir){
		perror("open dir failed");
		exit(0);
	}
	while((direc_entry = readdir(dir)) != NULL){
		printf("the directory entry inode is %lu record length is %d with file type\" %x \" and the name is %s \n ",direc_entry->d_ino,direc_entry->d_reclen,direc_entry->d_type,direc_entry->d_name);
		if((direc_entry->d_type == 4) && (memcmp(direc_entry->d_name,".",1))){

			ls_mock(direc_entry->d_name);
			printf("directory found\n");
		}	
	}
	return 0;
}
void main(){

//	ls_mock("../../system_programming");
	ls_mock(".");
	
}

