#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <pthread.h>

static int *account1, *account2;
pthread_mutex_t mut;
static int *sem1, *sem2, *sem3;

void* add1(void* arg){
	
	pthread_mutex_lock(&mut);
	if(*sem1 = 1){
		*sem1-=2;
		pthread_mutex_unlock(&mut);
		*account1 +=100;
		sleep(1);
		pthread_mutex_lock(&mut);
		*sem1+=2;
		pthread_mutex_unlock(&mut);
	} else {

		pthread_mutex_unlock(&mut);
	}
}

void* add2(void* arg){

	pthread_mutex_lock(&mut);
	if(*sem2 = 1){
		*sem2-=2;
		pthread_mutex_unlock(&mut);
		*account2 +=100;
		sleep(1);
		pthread_mutex_lock(&mut);
		*sem2+=2;
		pthread_mutex_unlock(&mut);
	}else {

		pthread_mutex_unlock(&mut);
	}
}

void* transfer(void* arg){
	pthread_mutex_lock(&mut);
	if(*sem3 = 1){
		*sem3-=2;
		if(*sem1==1){
			*sem1-=2;
			pthread_mutex_unlock(&mut);
			*account1-=100;
			sleep(1);
			pthread_mutex_lock(&mut);
			*sem1+=2;
			if(*sem2==1){
				*sem2-=2;
				pthread_mutex_unlock(&mut);
				*account2+=100;
				sleep(1);
				pthread_mutex_lock(&mut);
				*sem2+=2;
				*sem3+=2;
				pthread_mutex_unlock(&mut);
				
			}
		}
	}
}

int main(void){
	account1 = (int*)mmap(NULL, sizeof *account1, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	account2 = (int*)mmap(NULL, sizeof *account2, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

	sem1 = (int*)mmap(NULL, sizeof *sem1, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	sem2 = (int*)mmap(NULL, sizeof *sem2, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	*account1 = 0;
	*account2 = 0;
	pthread_mutex_init(&mut, NULL);
	int pid;
	*sem1 = 1;
	*sem2 = 1;
	
	pthread_t threads[20];

	for(int i=0; i<20; i++){
		if(rand()%2==1)
			pthread_create(&threads[i], NULL, add1, NULL);
		else

			pthread_create(&threads[i], NULL, add2, NULL);
	}
	
	printf("acc1: %d, acc2: %d", *account1, *account2);

	return 0;



}

