#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>
#define KEY 1232

union semun {
  int val;                  //used for SETVAL
  struct semid_ds *buf;     //used for IPC_STAT and IPC_SET
  unsigned short  *array;   //used for SETALL
  struct seminfo  *__buf;
};

int main(int argc, char *argv[]){
	if (argc >1){
		if (strcmp(argv[1], "create") == 0){
			int shmd;
			shmd = semget(KEY, 1, IPC_CREAT | IPC_EXCL | 0644);
			if (shmd == -1){
				printf("Semaphore already exists.\n");
				return 0;
			}
			union semun us;
			us.val = 1;
			printf("%d\n", us.val);
			return 0;
		}
		else if (strcmp(argv[1], "remove") == 0){
			int shmd;
			shmd = semget(KEY, 0, 0);
			if (shmd == -1){
				printf("Semaphore doesn't exist.\n");
				return 0;
			}
			semctl(shmd, 0, IPC_RMID);
			return 0;
		}
		printf("Invalid command. Use {create} or {remove}\n");
	}
	else{
		printf("Add a command: {create} or {remove}\n");
	}
	return 0;
}
