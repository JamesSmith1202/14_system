#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){
  if(argc < 2){
    printf("No arguments supplied\n");
    exit(0);
  }
  if (!strcmp(argv[1], "-c")){
    if(argc < 3){
      printf("No argument N supplied\n");
      exit(0);
    }
    int size = sizeof(argv[2]);
    int id = semget(ftok("./", 'm'), size, IPC_CREAT);
    if(id == -1){
      printf("Error: %s\n", strerror(errno));
    }
    else{
      printf("Semaphore created: %d\n", id);
      int val = semctl(id, 0, SETVAL, atoi(argv[2]));
      if(val == -1){
	printf("Error: %s\n", strerror(errno));
      }
      else{
	printf("Semaphore value set: %d\n", val);
      }
    }
  }
  else if (!strcmp(argv[1], "-v")){
    int id = semget(ftok("./", 'm'), 0, 0);
    int val = semctl(id, 0, GETVAL);
    if(val == -1){
      printf("Error: %s\n", strerror(errno));
    }
    else{
      printf("Semaphore value: %d\n", val);
    }
  }
  else if (!strcmp(argv[1], "-r")){
    int id = semget(ftok("./", 'm'), 0, 0);
    int val = semctl(id, 0, IPC_RMID);
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
