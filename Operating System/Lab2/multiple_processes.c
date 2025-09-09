#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int num_children = 5;
    pid_t pid;

    printf("Parent process with PID: %d\n", getpid());

    for (int i = 0; i < num_children; i++)
    {
        pid = fork();
        if (pid < 0)
        {
            perror("fork");
            exit(1);
        }
        else if (pid == 0)
        {
            printf("Child process %d, PID: %d\n", i + 1, getpid());
            exit(0);
        }
        else
        {
            printf("Parent created child %d, PID: %d\n", i + 1, pid);
        }
    }

    for (int i = 0; i < num_children; i++)
    {
        wait(NULL);
    }

    printf("Parent process complete\n");
    return 0;
}