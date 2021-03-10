#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <cstring>
#include <fcntl.h>

#define PATH "/tmp/pipe"

int main(){
	printf("mkfifo\n");
	mkfifo(PATH, 666);
	int pid;
	printf("open pipe\n");
	int read_id = open(PATH, 666);
	char arr2[10] = "asdfg";
	int fd;
	printf ("starting:\n");
	while(true){
		printf("sending\n");

		write(fd, "message", 8);
		}
}

