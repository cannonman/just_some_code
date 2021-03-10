#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstring>

char string1[] = "info from child aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n";
char string2[] = "info from parent\n";

int main(){
	int a = 64;
	int b = 65;
	int c = 66;
	int pid;
	printf("main process: %d \n",getpid());
	
	int fd[2], nbytes;
	pid_t childpid;
	char readbuffer[1020];
	int out;
	
	pipe(fd);

	switch (pid=fork()){
		case 0: // child
			printf("child process %d \n", getpid());
			sleep(2);
			printf ("a in child %d \n", a);
			out = dup(STDOUT_FILENO);
			close(fd[0]);
			dup2(fd[1], STDOUT_FILENO);
			execl("/bin/ls", "ls", "-l", NULL);
		//	write(fd[1], string1,(strlen(string1)+1));
			sleep(2);
			close(fd[1]);
			printf("end of child \n");
			exit(0);
			break;

		case -1: //error
			printf("error");
			break;

		default: //parent
			printf("pid: %d \n", pid);
			a++;
			printf("a in parent: %d \n", a);
			printf("parent process, %d \n", getppid());
			sleep(3);
			close(fd[1]);
			printf("aaaa\n");
			dup2(fd[0], 0);
			execl("/bin/grep", "grep", ".c", "-", NULL);
			printf("size: %d \n", strlen(readbuffer));
			wait(NULL);
			printf("main process: %d \n", getpid());
			exit(0);
	}
	exit(0);
}
