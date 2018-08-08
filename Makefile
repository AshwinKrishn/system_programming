c :
	rm *.out ashwin.txt trystat trylseek tryunlink tryreaddir

stat:
	gcc trystat.c -o trystat

lseeking :
	gcc lstattry.c  -o trylseek
delete :
	gcc unlinktry.c -o tryunlink
readdir:
	gcc readdirtry.c -o tryreaddir
