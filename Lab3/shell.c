#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstring>

int out;
int fd[2];


void first_pipe(int arg, char *argv[], int argc){
	int pid;
	char path [15] ={ "/bin/" } ;
	for (int i = 0; i<strlen(argv[arg]);i++){
		path[i+5] = argv[arg][i];
	}

	printf("%s, %s, %s \n", path, argv[arg], argv[arg+1]);
	switch(pid=fork()){
		case 0: //child
			dup2(0, fd[0]);
			close(fd[0]);
			dup2(fd[1], STDOUT_FILENO);
			printf("%s, %s, %s \n", path, argv[arg], argv[arg+1]);
			execl (path, argv[arg], argv[arg+1], NULL);
			break;
		case -1:
			printf("error");
			break;

		default: //parent
			close(fd[1]);
			if(arg+2<argc){
				first_pipe(arg+2, argv, argc);
					
			}
			wait(NULL);

	}
	exit(0);

}


int main(int argc, char *argv[]){
	
	first_pipe(1, argv, argc-1);
	return 0;
}
