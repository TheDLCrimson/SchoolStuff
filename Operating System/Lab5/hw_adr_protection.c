#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int globalVar = 0; // Global variable shared among processes
int main()
{
    printf("Parent Process: Initial globalVar = %d\n", globalVar);
    for (int i = 0; i < 10; i++)
    {
        pid_t pid = fork(); // Create a child process
        if (pid < 0)
        {
            perror("Fork failed");
            exit(1);
        }
        if (pid == 0)
        {
            // Child process
            printf("Child %d: Initial globalVar = %d\n", i, globalVar);
            // Modify the global variable
            globalVar += (i + 1) * 10;
            printf("Child %d: Modified globalVar = %d\n", i, globalVar);
            // Exit child process
            exit(0);
        }
    }
    // Wait for all child processes to finish
    for (int i = 0; i < 10; i++)
    {
        wait(NULL);
    }
    printf("Parent Process: Final globalVar = %d\n", globalVar);
    return 0;
}
