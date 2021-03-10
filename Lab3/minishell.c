#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstring>

int main(){
	int pid;
	int fd[2], nbytes;
	pid_t childpid;
	char readbuffer[1020];
	int out;
	char command[100];
	
	pipe(fd);

	switch (pid=fork()){
		case 0: // child
			printf("child process %d \n", getpid());
			sleep(2);
			printf ("a in child %d \n", a);
			out = dup(STDOUT_FILENO);
			close(fd[0]);
			dup2(fd[1], STDOUT_FILENO);
			execl("/bin/ls", "ls", "-l", NULL); //first command here
			close(fd[1]);
			printf("end of child \n");
			exit(0);
			break;

		case -1: //error
			printf("error");
			break;

		default: //parent
			sleep(3);
			close(fd[1]);
			dup2(fd[0], 0);
			execl("/bin/grep", "grep", ".c", "-", NULL); //second command
			wait(NULL);
			exit(0);
	}
	exit(0);
}
