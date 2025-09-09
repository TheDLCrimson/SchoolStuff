#include <stdio.h>
#include <pthread.h>

int shared_data = 0;
pthread_mutex_t lock;

void* increment(void* arg) {
    for (int i = 0; i < 100000; i++) {
        pthread_mutex_lock(&lock);  // Lock the critical section
        shared_data++;
        pthread_mutex_unlock(&lock);  // Unlock the critical section
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2;
    pthread_mutex_init(&lock, NULL);  // Initialize the mutex

    pthread_create(&thread1, NULL, increment, NULL);
    pthread_create(&thread2, NULL, increment, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Final value of shared_data: %d\n", shared_data);

    pthread_mutex_destroy(&lock);  // Destroy the mutex
    return 0;
}