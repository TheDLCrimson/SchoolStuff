#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int main()
{
    pid_t pid = fork();
    if (pid < 0)
    {
        perror("fork");
        exit(1);
    }
    else if (pid == 0)
    {
        printf("Child process with PID: %d\n", getpid());
        sleep(2);
        exit(0);
    }
    else
    {
        printf("Parent process waiting for child to finish...\n");
        wait(NULL);
        printf("Child has finished. Parent process continuing...\n");
    }
    return 0;
}