clean:
	rm forking_try execle_try pthreadtry resourcelimit lngjmp
execle:
	gcc execle_sysccall.c -o execle_try
forking:
	gcc forking.c -o forking_try 
thread:
	gcc pthread_try.c -o pthreadtry -lpthread
reslimit:
	gcc rlimit.c -o resourcelimit
longjmp:
	gcc longjumping.c -o lngjmp 
