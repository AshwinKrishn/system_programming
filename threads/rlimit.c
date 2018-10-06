#include <stdio.h>
#include <unistd.h>
#include <sys/resource.h>

int main()
{

	struct rlimit self_resource;
	int ret;

	ret = getrlimit(RLIMIT_MEMLOCK, &self_resource);
	if(ret == -1){
		perror("Error while getting limit");
	}
	
	printf("initial result limit min %ld max %ld  ",self_resource.rlim_max, self_resource.rlim_cur);
	
	self_resource.rlim_max = 65536;
	self_resource.rlim_cur = 65536;

	ret = setrlimit(RLIMIT_MEMLOCK,&self_resource);
	if(ret == -1){
                perror("Error while setting limit");
        }
	ret = getrlimit(RLIMIT_MEMLOCK, &self_resource);
        if(ret == -1){ 
                perror("Error while getting limit");
        }
	printf("relimit min %ld max %ld  ",self_resource.rlim_max, self_resource.rlim_cur);

}
