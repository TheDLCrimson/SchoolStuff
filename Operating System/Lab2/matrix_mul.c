#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 3
#define M 3
#define P 3

int A[N][M] = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9}};

int B[M][P] = {
    {9, 8, 7},
    {6, 5, 4},
    {3, 2, 1}};

int C[N][P];

typedef struct
{
    int row;
    int col;
} thread_data_t;

void *calculate_element(void *arg)
{
    thread_data_t *data = (thread_data_t *)arg;
    int row = data->row;
    int col = data->col;

    C[row][col] = 0;
    for (int k = 0; k < M; k++)
    {
        C[row][col] += A[row][k] * B[k][col];
    }

    pthread_exit(0);
}

int main()
{
    pthread_t threads[N * P];
    thread_data_t thread_data[N * P];
    int thread_count = 0;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < P; j++)
        {
            thread_data[thread_count].row = i;
            thread_data[thread_count].col = j;

            pthread_create(&threads[thread_count], NULL, calculate_element, &thread_data[thread_count]);
            thread_count++;
        }
    }

    for (int i = 0; i < thread_count; i++)
    {
        pthread_join(threads[i], NULL);
    }

    printf("Resultant Matrix C:\n");
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < P; j++)
        {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

    return 0;
}