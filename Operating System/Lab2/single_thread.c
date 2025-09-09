#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *print_message(void *arg)
{
    printf("Hello from the VinUni!\n");
    pthread_exit(NULL);
}

int main()
{
    pthread_t thread;
    int result;

    result = pthread_create(&thread, NULL, print_message, NULL);
    if (result != 0)
    {
        printf("Error creating thread\n");
        return 1;
    }

    pthread_join(thread, NULL);

    printf("Thread has finished execution.\n");
    return 0;
}