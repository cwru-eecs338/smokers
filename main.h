#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/errno.h>
#include <sys/time.h>
#include <time.h>
#include <sys/wait.h>

#define SEMKEY 77
#define SHMKEY 77

#define NUM_SEMS   2
#define SEM_AGENT  0
#define SEM_SMOKER 1

#define TOBACCO 0
#define MATCHES 1
#define PAPER   2

#define K 1024

struct common {
	int item1;
	int item2;
	long lastwrite;
	long lastwriteu;
	int agentpid;
	int smokerpid;
};

void P(int semid, int semaphore)
{
	struct sembuf psembuf;

	psembuf.sem_op = -1;
	psembuf.sem_flg = 0;
	psembuf.sem_num = semaphore;
	semop(semid,&psembuf,1);
	return;
}

void V(int semid, int semaphore)
{
	struct sembuf vsembuf;

	vsembuf.sem_op = 1;
	vsembuf.sem_flg = 0;
	vsembuf.sem_num = semaphore;
	semop(semid,&vsembuf,1);
	return;
}

void writeitem(int item)
{
	switch (item) {
		case TOBACCO:
			printf("tobacco");
			break;
		case MATCHES:
			printf("matches");
			break;
		case PAPER:
			printf("paper");
			break;
	};
	return;
}

union semun {
	/* value for SETVAL */
	int val;
	/* buffer for IPC_STAT, IPC_SET */
	struct semid_ds *buf;
	/* array for GETALL, SETALL */
	unsigned short *array;
	/* Linux specific part: */
	/* buffer for IPC_INFO */
	struct seminfo *__buf;
};
