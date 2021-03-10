#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>

int main(){
	const int segment_size = 256;
	int segment_id = shmget(IPC_PRIVATE, segment_size, IPC_CREAT | IPC_EXCL );
	
	char * shared_memory;
	shared_memory = (char*) shmat (segment_id, 0, 0);
	sprintf (shared_memory, "text");
	shmdt(shared_memory);

	return 0;

}
