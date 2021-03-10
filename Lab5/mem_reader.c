#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>

int main(){
	const int segment_size = 256;
	int segment_id = shmget(0, segment_size, IPC_CREAT | IPC_EXCL );
	
	int * shared_memory;
	shared_memory = (int*) shmat (segment_id, 0, 0);
	printf ("memory:%d\n", 10);
	sleep(10);
	shmdt(shared_memory);

	return 0;

}
