#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

sem_t forks[NUM_PHILOSOPHERS];

void *philosopher(void *num)
{
    int id = *(int *)num;

    while (1)
    {
        printf("Philosopher %d is Thinking\n", id + 1);
        sleep(1);

        printf("Philosopher %d is Hungry\n", id + 1);

        sem_wait(&forks[id]);

        sem_wait(&forks[(id + 1) % NUM_PHILOSOPHERS]);

        printf("Philosopher %d takes Fork %d and Fork %d\n", id + 1, id + 1, (id + 2) % NUM_PHILOSOPHERS);

        printf("Philosopher %d is Eating\n", id + 1);
        sleep(1);

        sem_post(&forks[id]);
        sem_post(&forks[(id + 1) % NUM_PHILOSOPHERS]);
        printf("Philosopher %d putting Fork %d and Fork %d down\n", id + 1, id + 1, (id + 2) % NUM_PHILOSOPHERS);
    }
}

int main()
{
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int ids[NUM_PHILOSOPHERS];

    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        sem_init(&forks[i], 0, 1);
        ids[i] = i;
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);

    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
        pthread_join(philosophers[i], NULL);

    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
        sem_destroy(&forks[i]);

    return 0;
}
