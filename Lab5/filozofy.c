#include <sys/types.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdlib.h>
#include <stdio.h>

#define PERM 0600
#define KEY ((key_t)12345L)



int main(int argc, char *argv[]){
	short fil_id =*argv[argc-1];
	int semid;
	int x;
	if((semid=semget(KEY, 5, PERM | IPC_CREAT)) < 0) {
		printf("nie mozna utworzyc semafora");
		exit(1);
	}
	
	

	struct sembuf get[2];
	get[0]={
	fil_id, -1, 0;
	};
	get[1]={
	fil_id+1, -1, 0;
	};


	struct sembuf wait[2];
	get[0]={
	fil_id, 0, 0
	};
	get[1]={
	fil_id+1, 0, 0
	};

	struct sembuf leave[2];
	leave[0]={
	fil_id, 1, 0
	};
	leave[1]={
	fil_id+1, 1, 0
	};

	
	while(true){
	
		printf("filozof %d zaczyna probowac jesc\n", fil_id);	

		semop(KEY, wait, 2);
		semop(KEY, get, 2); //proba zjedznenia


		//jedzenie
		x = (rand()%10)+2;
		printf ("filozof %d zaczyna jesc, %d s\n",fil_id,  x);
		sleep(x);
		//zwolnienie widelcow

		semop(KEY, leave, 2);

		printf ("filozof %d skonczyl jesc, idzie medytowac\n", fil_id);
		x = (rand()%10) + 2;
		sleep(x);
		printf ("filozof %d skonczyl medytowac, (%d s), idize jesc\n", fil_id, x);

	}
}
