#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#define KEY 1232

int main(){
	int semd = semget(KEY, 1, 0); //get access
	struct sembuf sb;
	sb.sem_num = 0;
	sb.sem_flg = SEM_UNDO;
	sb.sem_op = -1; //setting the operation to down
	semop(semd, &sb, 1); //perform the operation
	printf("got the semaphore!\n");
	printf("sd\n"); //simulate doing something.
	sb.sem_op = 1; //set the operation to up
	semop(semd, &sb, 1); //perform the operation
}
