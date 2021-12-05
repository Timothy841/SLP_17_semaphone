#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/shm.h>
#include <fcntl.h>
#include <unistd.h>
#define SEMKEY 1232
#define SHMKEY 1233

int main(){
	int semd = semget(SEMKEY, 0, 0); //get access
	int shmd = semget(SHMKEY, 0, 0);
	if (semd == -1){
		printf("Semaphore doesn't exist. Create one first.\n");
		return 0;
	}
	char c[100];
	struct sembuf sb;
	sb.sem_num = 0;
	sb.sem_flg = SEM_UNDO;
	sb.sem_op = -1; //setting the operation to down
	semop(semd, &sb, 1); //perform the operation
	int *line = shmat(shmd, 0, 0);
	struct stat info;
	stat("story.txt", &info);
	int file = open("story.txt", O_RDONLY);
	if (file.st_size > 0){
		lseek(file, *line * -1, SEEK_END);
		read(file, c, *line);
		printf("Current line: $s\n", c);
	}
	else{
		printf("New story: \n");
	}
	close(file);
	file = open("story.txt", O_WRONLY, O_APPEND);
	fgets(c, strlen(c), stdin);
	write(file, c, strlen(c));
	close(file);
	shmdt(line);
	sb.sem_op = 1; //set the operation to up
	semop(semd, &sb, 1); //perform the operation
}
