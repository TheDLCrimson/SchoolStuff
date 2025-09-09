#include <stdio.h>
#include <stdbool.h>

#define NUM_PROCESSES 5
#define NUM_RESOURCES 3

void calculateNeed(int need[NUM_PROCESSES][NUM_RESOURCES], int max[NUM_PROCESSES][NUM_RESOURCES], int allocation[NUM_PROCESSES][NUM_RESOURCES])
{
    for (int i = 0; i < NUM_PROCESSES; i++)
        for (int j = 0; j < NUM_RESOURCES; j++)
            need[i][j] = max[i][j] - allocation[i][j];
}

void printNeedMatrix(int need[NUM_PROCESSES][NUM_RESOURCES])
{
    for (int i = 0; i < NUM_PROCESSES; i++)
    {
        printf("P%d: ", i);
        for (int j = 0; j < NUM_RESOURCES; j++)
            printf("%d ", need[i][j]);
        printf("\n");
    }
}

bool isSafe(int available[NUM_RESOURCES], int max[NUM_PROCESSES][NUM_RESOURCES], int allocation[NUM_PROCESSES][NUM_RESOURCES])
{
    int need[NUM_PROCESSES][NUM_RESOURCES];
    calculateNeed(need, max, allocation);

    bool finish[NUM_PROCESSES] = {0};
    int safeSequence[NUM_PROCESSES];
    int work[NUM_RESOURCES];

    for (int i = 0; i < NUM_RESOURCES; i++)
        work[i] = available[i];

    int count = 0;
    while (count < NUM_PROCESSES)
    {
        bool found = false;
        for (int p = 0; p < NUM_PROCESSES; p++)
        {
            if (!finish[p])
            {
                int j;
                for (j = 0; j < NUM_RESOURCES; j++)
                    if (need[p][j] > work[j])
                        break;

                if (j == NUM_RESOURCES)
                {
                    for (int k = 0; k < NUM_RESOURCES; k++)
                        work[k] += allocation[p][k];
                    safeSequence[count++] = p;
                    finish[p] = true;
                    found = true;
                }
            }
        }

        if (!found)
        {
            printf("System is not in a safe state.\n");
            return false;
        }
    }

    printf("System is in a safe state.\nSafe sequence is: ");
    for (int i = 0; i < NUM_PROCESSES; i++)
        printf("P%d ", safeSequence[i]);

    printf("\n");

    return true;
}

int main()
{
    int allocation[NUM_PROCESSES][NUM_RESOURCES] = {
        {1, 1, 2},
        {2, 1, 2},
        {3, 0, 1},
        {0, 2, 0},
        {1, 1, 2}};

    int max[NUM_PROCESSES][NUM_RESOURCES] = {
        {5, 4, 4},
        {4, 3, 3},
        {9, 1, 3},
        {8, 6, 4},
        {2, 2, 3}};

    int available[NUM_RESOURCES] = {3, 2, 1};

    int need[NUM_PROCESSES][NUM_RESOURCES];
    calculateNeed(need, max, allocation);
    printf("Need Matrix:\n");
    printNeedMatrix(need);

    isSafe(available, max, allocation);

    return 0;
}