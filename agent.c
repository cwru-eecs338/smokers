#include "hw4.h"

int rand0to2 ()
{
    short randval = 3;

    while (randval > 2)
        randval = (rand() & 0x0300) >> 8;
    return (int)randval;
}

main ()
{
    int semid, shmid;
    struct common *shared;
    struct timeval tp;
    int loop;
    short item;

    int mypid=getpid();
    srand(mypid);

    semid=semget(SEMKEY,NUM_SEMS,0777);
    shmid=shmget(SHMKEY,1*K,0777);
    shared=(struct common *)shmat(shmid,0,0);

    for (loop=1; loop<15; loop++) {
	P(semid,SEM_AGENT);
	shared->item1 = rand0to2();
	shared->item2 = rand0to2();
	while (shared->item1 == shared->item2)
	    shared->item2 = rand0to2();
	printf("AGENT (pid %d) generates materials...\n",mypid);
	printf("The items ");
	writeitem(shared->item1);
	printf(" and ");
	writeitem(shared->item2);
	printf(" are now available.\n\n");
	shared->agentpid = mypid;
	V(semid,SEM_SMOKER);
	};
}
