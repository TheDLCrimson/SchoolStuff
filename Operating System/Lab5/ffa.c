#include <stdio.h>

void firstFit(int blockSize[], int m, int processSize[], int n)
{
    int allocation[n];
    int internalFrag[n];
    for (int i = 0; i < n; i++)
    {
        allocation[i] = -1;
        internalFrag[i] = 0;
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            if (blockSize[j] >= processSize[i])
            {
                allocation[i] = j;
                internalFrag[i] = blockSize[j] - processSize[i];
                blockSize[j] -= processSize[i];
                break;
            }
    }

    int externalFrag = 0;
    for (int j = 0; j < m; j++)
        externalFrag += blockSize[j];

    printf("\nFirst Fit:\n");
    printf("Process No.\tProcess Size\tBlock No.\tInternal Fragmentation\n");

    for (int i = 0; i < n; i++)
    {
        printf("%d\t\t%d\t\t", i + 1, processSize[i]);
        if (allocation[i] != -1)
            printf("%d\t\t%d\n", allocation[i] + 1, internalFrag[i]);
        else
            printf("Not Allocated\t-\n");
    }

    printf("Total External Fragmentation: %d KB\n", externalFrag);
}

int main()
{
    int blockSize[] = {100, 500, 200, 300, 600};
    int processSize[] = {212, 417, 112, 426};
    int m = sizeof(blockSize) / sizeof(blockSize[0]);
    int n = sizeof(processSize) / sizeof(processSize[0]);

    firstFit(blockSize, m, processSize, n);

    return 0;
}