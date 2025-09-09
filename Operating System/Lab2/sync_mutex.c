#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#define NUM_THREADS 5
#define INCREMENTS_PER_THREAD 100000
long long shared_counter = 0;
pthread_mutex_t mutex;
void *increment_counter(void *arg)
{
    for (int i = 0; i < INCREMENTS_PER_THREAD; i++)
    {
        pthread_mutex_lock(&mutex);
        shared_counter++;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}
int main()
{
    pthread_t threads[NUM_THREADS];
    pthread_mutex_init(&mutex, NULL);
    for (int i = 0; i < NUM_THREADS; i++)
    {
        if (pthread_create(&threads[i], NULL, increment_counter, NULL) != 0)
        {
            perror("Failed to create thread");
            return 1;
        }
    }
    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }
    printf("Final counter value: %lld\n", shared_counter);
    pthread_mutex_destroy(&mutex);
    return 0;
}