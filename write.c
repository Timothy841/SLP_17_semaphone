#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#define KEY 1232

int main(){
	int shmd;
	shmd = semget(KEY, 0, 0);
	if (shmd == -1){
		printf("No Semaphore. Please create one first.\n");
	}
	Down(shmd);
	printf("%s\n", "es");
	wait(1000);
	printf("%s\n", "es");
}
