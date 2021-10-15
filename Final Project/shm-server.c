#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHMSIZE 100

int main(int argc, char *argv[])
{
  int shmid;
  key_t key;
  char *shm;
  char *s;
  
  key = 9876;
  
  shmid = shmget(key, SHMSIZE, IPC_CREAT | 0666);
  
  if (shmid < 0)
  {
    perror("There's a problem with 'shmget' function");
    EXIT_FAILURE;
  }
  
  shm = shmat(shmid, NULL, 0);
  
  if (shm == (char *) - 1)
  {
    perror("There's a problem with 'shmat' function");
    EXIT_FAILURE;
  }
  char message[] = "One Client has been connected to the server!";
  memcpy(shm, message, sizeof(message));
  
  s = shm;
  s += sizeof(message);
  *s = 0;
    
}
