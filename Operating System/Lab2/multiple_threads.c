#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define NUM_THREADS 5
typedef struct
{
    int thread_id;
    int sum;
} thread_data_t;
void *compute_sum(void *arg)
{
    thread_data_t *data = (thread_data_t *)arg;
    data->sum = 0;
    for (int i = 1; i <= 10; i++)
    {
        data->sum += i + data->thread_id * 10;
    }
    printf("Thread %d calculated sum: %d\n", data->thread_id, data->sum);
    pthread_exit(NULL);
}
int main()
{
    pthread_t threads[NUM_THREADS];
    thread_data_t thread_data[NUM_THREADS];
    for (int i = 0; i < NUM_THREADS; i++)
    {
        thread_data[i].thread_id = i;
        int result = pthread_create(&threads[i], NULL, compute_sum, &thread_data[i]);
        if (result != 0)
        {
            printf("Error creating thread %d\n", i);
            return 1;
        }
    }
    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }
    printf("All threads have finished execution.\n");
    return 0;
}