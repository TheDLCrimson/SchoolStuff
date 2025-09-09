#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 4

struct Node
{
    int data;
    struct Node *next;
};

struct Node *head = NULL;

struct Node *create_node(int data)
{
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void append_node(int data)
{
    struct Node *new_node = create_node(data);
    if (head == NULL)
    {
        head = new_node;
    }
    else
    {
        struct Node *temp = head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

typedef struct
{
    struct Node *start;
    int chunk_size;
    int partial_sum;
} thread_data_t;

void *sum_chunk(void *arg)
{
    thread_data_t *data = (thread_data_t *)arg;
    struct Node *current = data->start;
    data->partial_sum = 0;

    for (int i = 0; i < data->chunk_size && current != NULL; i++)
    {
        data->partial_sum += current->data;
        current = current->next;
    }

    pthread_exit(NULL);
}

int main()
{

    for (int i = 1; i <= 20; i++)
    {
        append_node(i);
    }

    int total_nodes = 20;
    int chunk_size = total_nodes / NUM_THREADS;

    pthread_t threads[NUM_THREADS];
    thread_data_t thread_data[NUM_THREADS];
    struct Node *current = head;
    int total_sum = 0;

    for (int i = 0; i < NUM_THREADS; i++)
    {
        thread_data[i].start = current;
        thread_data[i].chunk_size = chunk_size;

        for (int j = 0; j < chunk_size && current != NULL; j++)
        {
            current = current->next;
        }

        // Create a new thread
        pthread_create(&threads[i], NULL, sum_chunk, &thread_data[i]);
    }

    // Wait for all threads to complete and accumulate the results
    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
        total_sum += thread_data[i].partial_sum;
    }

    printf("Total sum of linked list: %d\n", total_sum);
    return 0;
}