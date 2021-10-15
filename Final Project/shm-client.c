#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHMSIZE 100

int main(int argc, char *argv[])
{
	if(argc < 2){
		printf("The number of entered arguments is less that two ! it should be like ./shm-client 'text'");
		exit(EXIT_FAILURE);
	}
	int shmid;
	key_t key;
	char *shm;
	char *s;
	char* text = (char *)argv[1];
	key = 9876;
	
	shmid = shmget(key, SHMSIZE, 0666);
	
	if (shmid < 0)
	{
		perror("There's a problem with 'shmget' function");
		exit(EXIT_FAILURE);
	}
	
	shm = shmat(shmid, NULL, 0);
	
	if (shm == (char *) - 1)
	{
		perror("There's a problem with 'shmat' function");
		exit(EXIT_FAILURE);
	}
	
	for(s = shm; *s != 0; s++)
		printf("%c", *s);
	
	printf("\n");
	
	*shm = '#';
	
	return 0;	
}
