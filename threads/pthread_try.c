#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

void * abspid(void * arg){
	
	int a  =*( (int *)(arg));
	printf("thread guy input %d and the pid is %d parent is %d\n",a,getpid(),getppid());


}

int main(){

	pthread_t t1;
	pthread_t t2;
	int t1_c = 5;
	int t2_c = 8; 

	printf("father pid is %d\n",getpid());
	pthread_create(&t1,NULL,abspid,(void *)&t1_c);
	pthread_create(&t2,NULL,abspid,(void *)&t2_c);

	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	return 0;

}
