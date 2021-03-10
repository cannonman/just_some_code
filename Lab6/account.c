#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <pthread.h>
static int *account;
sem_t sem;

void* thread(void* arg){
	for(int i = 0; i<5; i++){
		sem_wait(&sem);
		printf("starting operation\n");
		*account += 100;
		sleep(rand()%5);
		printf("account: %d\n", *account);
		sem_post(&sem);
	}

}

int main(void){
	account = (int*)mmap(NULL, sizeof *account, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

	*account = 0;
	sem_init(&sem, 1, 1);
	int pid;

	pthread_t t1, t2;
	pthread_create(&t1, NULL, thread, NULL);
	pthread_create(&t2, NULL, thread, NULL);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	sem_destroy(&sem);
	return 0;



}

