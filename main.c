#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <fcntl.h>
#include <unistd.h>
#define SEMKEY 1232
#define SHMKEY 1233

union semun {
  int val;                  //used for SETVAL
  struct semid_ds *buf;     //used for IPC_STAT and IPC_SET
  unsigned short  *array;   //used for SETALL
  struct seminfo  *__buf;
};

int main(int argc, char *argv[]){
	if (argc >1){
		if (strcmp(argv[1], "create") == 0){
			int semd = semget(SEMKEY, 1, IPC_CREAT | IPC_EXCL | 0644);
      int shmd = shmget(SHMKEY, sizeof(int), IPC_CREAT | IPC_EXCL | 0644);
			if (semd == -1){
				printf("Semaphore already exists.\n");
				return 0;
			}
			union semun us;
			us.val = 1;
			semctl(semd, 0, SETVAL, us);
			int file = open("story.txt",O_CREAT | O_WRONLY | O_TRUNC, 0644);
			close(file);
			return 0;
		}
		else if (strcmp(argv[1], "remove") == 0){
			int semd = semget(SEMKEY, 0, 0);
			int shmd = shmget(SHMKEY, 0, 0);
			if (semd == -1){
				printf("Semaphore doesn't exist.\n");
				return 0;
			}
			shmctl(shmd, IPC_RMID, 0);
			semctl(semd, 0, IPC_RMID);
      int file = open("story.txt", O_RDONLY);
			struct stat info;
			stat("story.txt", &info);
			char *story = malloc(info.st_size + 1);
			story[info.st_size] = '\0';
			read(file, story, info.st_size);
			printf("Story:\n%s", story);
			free(story);
			close(file);
			return 0;
		}
		printf("Invalid command. Use {create} or {remove}\n");
	}
	else{
		printf("Add a command: {create} or {remove}\n");
	}
	return 0;
}
