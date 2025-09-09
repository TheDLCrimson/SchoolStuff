#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#define SHM_SIZE 1024

int main()
{
    pid_t pid;
    key_t key = ftok("shmfile", 65);
    int shmid;
    char *shared_memory;

    shmid = shmget(key, SHM_SIZE, 0666 | IPC_CREAT);
    if (shmid == -1)
    {
        perror("shmget failed");
        exit(1);
    }

    pid = fork();
    if (pid < 0)
    {
        perror("fork failed");
        exit(1);
    }

    if (pid == 0)
    {

        shared_memory = (char *)shmat(shmid, NULL, 0);
        if (shared_memory == (char *)-1)
        {
            perror("shmat failed");
            exit(1);
        }

        printf("Child process writing to shared memory...\n");
        strncpy(shared_memory, "Hello from child process!", SHM_SIZE);
        shmdt(shared_memory);
        printf("Child process finished writing.\n");
        exit(0);
    }
    else
    {

        wait(NULL);
        shared_memory = (char *)shmat(shmid, NULL, 0);
        if (shared_memory == (char *)-1)
        {
            perror("shmat failed");
            exit(1);
        }

        printf("Parent process reading from shared memory...\n");
        printf("Data read from shared memory: %s\n", shared_memory);
        shmdt(shared_memory);
        shmctl(shmid, IPC_RMID, NULL);
        printf("Parent process finished reading and cleaned up shared memory.\n");
    }

    return 0;
}