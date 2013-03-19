#include "main.h"

int main ()
{
    FILE *fp;
    int semid,shmid,pid1,pid2,pid3,pid4;
    unsigned short seminit[NUM_SEMS];
    struct common *shared;
    union semun semctlarg;

    semid=semget(SEMKEY,NUM_SEMS,0777|IPC_CREAT);
    seminit[SEM_AGENT]=1;
    seminit[SEM_SMOKER]=0;
    semctlarg.array = seminit;
    semctl(semid,NUM_SEMS,SETALL,semctlarg);

    shmid=shmget(SHMKEY,1*K,0777|IPC_CREAT);
    shared=(struct common *)shmat(shmid,0,0);
    shared->item1=0;
    shared->item2=0;
    shared->agentpid=0;
    shared->smokerpid=0;

    if ((pid1=fork())==0) {
	execl("agent.bin","agent",0);
	exit(EXIT_SUCCESS);
	}
    else if ((pid2=fork())==0) {
	execl("smoker.bin","smoker","0",0);
	exit(EXIT_SUCCESS);
	}
    else if ((pid3=fork())==0) {
        execl("smoker.bin","smoker","1",0);
	exit(EXIT_SUCCESS);
	}
    else if ((pid4=fork())==0) {
	execl("smoker.bin","smoker","2",0);
	exit(EXIT_SUCCESS);
	};

    fp=fopen("smokers.kill","w");
    fprintf(fp,"kill %d\n",pid1);
    fprintf(fp,"kill %d\n",pid2);
    fprintf(fp,"kill %d\n",pid3);
    fprintf(fp,"kill %d\n",pid4);
    fclose(fp);

    wait(0);
    sleep(2);
    printf("Agent terminated...KILLING SMOKERS!\n");
    kill(pid2,SIGKILL);
    kill(pid3,SIGKILL);
    kill(pid4,SIGKILL);

    wait(0);
    wait(0);
    wait(0);
    printf("Children terminated...CLEANING UP!\n");

    semctl(semid,NUM_SEMS,IPC_RMID,0);
    shmctl(shmid,IPC_RMID,0);
}
