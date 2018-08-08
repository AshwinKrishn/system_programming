#include <stdio.h>
#include <error.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

void main(){


	struct stat  ff;

	int a = stat("lstattry.c",&ff);
	if(a == -1){

		perror("STAT COMMAND");
	}
	printf("ID of the device containing the file %lu\n",ff.st_dev);	
	printf("Inode number of the file is %lu\n",ff.st_ino);	
	printf("Number of hand links for the file %lu",ff.st_nlink);
	printf("protection the file %u\n",ff.st_mode);	
	printf("GID of the file %u\n",ff.st_gid);	
	printf("UID of the file %u\n",ff.st_uid);	
	printf("size of the file %lu\n",ff.st_size);	
	printf("blocksize of the file system %lu\n",ff.st_blksize);	
	printf("number of 512B blocks allocated for the file %lu\n",ff.st_blocks);	
	printf("last time accessed %ld\n",ff.st_atim.tv_sec);
	printf("last time modified %ld\n",ff.st_mtim.tv_sec);
	printf("last time status changed %ld\n",ff.st_ctim.tv_sec);
	
	
}
