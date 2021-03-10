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
	printf("open\n");
	char buffer [100];
	printf("starting \n");
	while(true){
		int read_id = open(PATH, 666);
		printf("reading %d \n", read_id);
		int read_status = read(read_id, buffer, sizeof(buffer));
		if (read_status == 0){
			printf("return from pipe:\n");

			for (int i = 0; i<strlen(buffer);i++){
				printf("%c", buffer[i]);	
				}
			close(read_id);
		} else {
		printf ("EOF, %d", read_status);
		}
		perror(NULL);
		}
	}

