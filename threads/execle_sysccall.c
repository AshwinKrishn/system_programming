#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(){

	char * env[] = {"USER = root",NULL};

	execle("/bin/sh" , "sh" , NULL , env);

	return 0; 


}

