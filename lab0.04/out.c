#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <time.h>
#include <sys/shm.h>
#include <string.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <signal.h>

#define FILE "shared_memory"

struct sembuf sem_lock = {0,-1,0}, sem_open = {0,1,0};

int shmid;

void funcExit(int sig)
{
    printf("\n");
    struct shmid_ds *buf = 0;
    shmctl(shmid, IPC_RMID, buf);

    exit(0);
}

int main(int argc, char* argv[])
{
    signal(SIGINT, funcExit);
    char * addr;
    key_t key = ftok(FILE, 'a');
    key_t semkey = ftok("/tmp", 'a');
    shmid = (shmget(key, 32, IPC_CREAT | 0666));
    int semid = (semget(semkey, 1, IPC_CREAT | 0666));

    if(semid == -1)
    {
        printf("Sem create err\n");
        exit(0);
    }

    if( shmid == -1 )
    {
        printf("Can't create shared memory\n");
        exit(0);
    }

    if((addr = shmat( shmid, NULL, 0 )) == (char*)-1)
    {
        printf("Shmat err\n");
    }

    time_t timer = time(0);
    time_t buft = timer;
    int check = 1;

    if (argc > 1)
    {
        if (strcmp(argv[1],"-f") == 0)
        {
            check = 1;
        }
        else
        {
            printf("such a key is not processed\n");
            exit(0);
        }
    } 
    else
    {
        if (strlen(addr) != 0)
            {   
                printf("there is already a sending process\n");
                printf("if you want to clear memory, run the program with the flag -f\n");
                check = 0;
                exit(0);
            }
    }
    //semop(semid, &sem_open, 1);
    while(check > 0)
    {
        timer = time(0);
        if(timer != buft)
        {
            semop(semid, &sem_open, 1);
            buft = timer;
            sprintf(addr, "time_Producer = %spid_Producer = %d\n", ctime(&timer), getpid());
            sleep(1);
            semop(semid, &sem_lock, 1);
        }
    }
    return 0;
}