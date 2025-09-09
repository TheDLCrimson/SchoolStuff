#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;
    int status;

    pid = fork();

    if (pid < 0)
    {
        perror("fork failed");
        exit(1);
    }
    else if (pid == 0)
    {
        printf("Child process PID: %d\n", getpid());
        while (1)
        {
        }
    }
    else
    {
        printf("Parent process PID: %d. Waiting for a few seconds before terminating child with kill()...\n", getpid());
        sleep(3);

        kill(pid, SIGTERM);

        wait(&status);
        if (WIFEXITED(status))
        {
            printf("Child terminated normally with exit status: %d\n", WEXITSTATUS(status));
        }
        else if (WIFSIGNALED(status))
        {
            printf("Child was terminated by a signal: %d\n", WTERMSIG(status));
        }

        printf("Parent process finished.\n");
    }

    pid = fork();
    if (pid < 0)
    {
        perror("fork failed");
        exit(1);
    }
    else if (pid == 0)
    {
        printf("Child process PID: %d running infinite loop...\n", getpid());
        while (1)
        {
            
        }
    }
    else
    {
        printf("Parent process PID: %d. Waiting for a few seconds before terminating child with abort()...\n", getpid());
        sleep(3);
        kill(pid, SIGABRT);
        wait(&status);
        if (WIFEXITED(status))
        {
            printf("Child terminated normally with exit status: %d\n", WEXITSTATUS(status));
        }
        else if (WIFSIGNALED(status))
        {
            printf("Child was terminated by a signal: %d\n", WTERMSIG(status));
        }
        printf("Parent process finished after terminating child with abort().\n");
    }

    pid = fork();
    if (pid < 0)
    {
        perror("fork failed");
        exit(1);
    }
    else if (pid == 0)
    {
        printf("Child process PID: %d will exit normally with code 0...\n", getpid());
        exit(0);
    }
    else
    {
        printf("Parent process PID: %d waiting for child to exit normally...\n", getpid());
        wait(&status);
        if (WIFEXITED(status))
        {
            printf("Child terminated normally with exit status: %d\n", WEXITSTATUS(status));
        }
        else if (WIFSIGNALED(status))
        {
            printf("Child was terminated by a signal: %d\n", WTERMSIG(status));
        }
        printf("Parent process finished after child exited normally.\n");
    }

    return 0;
}
