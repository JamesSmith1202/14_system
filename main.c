#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){
  int id;
  int val;
  int key = ftok("./", 'm');
  if(argc < 2){
    printf("No arguments supplied\n");
    exit(0);
  }
  if (!strcmp(argv[1], "-c")){
    if(argc < 3){
      printf("No argument N supplied\n");
      exit(0);
    }
    int size = sizeof(int);
    id = semget(key, size, IPC_CREAT | IPC_EXCL | 0644);
    if(id == -1){
      printf("Error: %s\n", strerror(errno));
    }
    else{
      printf("Semaphore created: %d\n", id);
      val = semctl(id, 0, SETVAL, atoi(argv[2]));
      if(val == -1){
	printf("Error: %s\n", strerror(errno));
      }
      else{
	printf("Semaphore value set: %d\n", atoi(argv[2]));
      }
    }
  }
  else if (!strcmp(argv[1], "-v")){
    id = semget(key, 0, 0);
    val = semctl(id, 0, GETVAL);
    if(val == -1){
      printf("Error: %s\n", strerror(errno));
    }
    else{
      printf("Semaphore value: %d\n", val);
    }
  }
  else if (!strcmp(argv[1], "-r")){
    id = semget(key, 0, 0);
    val = semctl(id, 0, IPC_RMID);
    if(val == -1){
      printf("Error: %s\n", strerror(errno));
    }
    else{
      printf("Semaphore removed: %d\n", val);
    }
  }
  else{
    printf("Invalid command!\n");
  }
  return 0;
}
