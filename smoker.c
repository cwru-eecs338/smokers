#include "main.h"

main (int argc, char *argv[])
{
    int semid, shmid;
    struct common *shared;

    int mypid=getpid();
    int smokernum=atoi(argv[1]);

    semid=semget(SEMKEY,NUM_SEMS,0777);
    shmid=shmget(SHMKEY,1*K,0777);
    shared=(struct common *)shmat(shmid,0,0);

    while (1) {
	P(semid,SEM_SMOKER);
	if ((shared->item1 != smokernum) && (shared->item2 != smokernum)) {
	    printf("SMOKER %d (pid %d) smokes...\n",smokernum,mypid);
	    printf("This smoker has ");
	    writeitem(smokernum);
	    printf(".  The items ");
	    writeitem(shared->item1);
	    printf(" and ");
	    writeitem(shared->item2);
	    printf(" are available.\n\n");
	    shared->smokerpid = mypid;
	    V(semid,SEM_AGENT);
	} else
    	    V(semid,SEM_SMOKER);
    }
}
