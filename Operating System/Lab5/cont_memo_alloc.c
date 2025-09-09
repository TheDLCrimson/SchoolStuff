#include <stdio.h>
#include <stdbool.h>

void firstFit(int blockSize[], int m, int processSize[], int n)
{
    int allocation[n];
    int internalFrag[n];
    bool taken[m];
    for (int i = 0; i < n; i++)
    {
        allocation[i] = -1;
        internalFrag[i] = 0;
    }

    for (int i = 0; i < m; i++)
        taken[i] = false;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            if (blockSize[j] >= processSize[i] && !taken[j])
            {
                allocation[i] = j;
                internalFrag[i] = blockSize[j] - processSize[i];
                blockSize[j] -= processSize[i];
                taken[j] = true;
                break;
            }
    }

    int externalFrag = 0;
    int sumInternalFrag = 0;
    for (int j = 0; j < m; j++)
    {
        if (!taken[j])
            externalFrag += blockSize[j];
        else
            sumInternalFrag += blockSize[j];
    }
    int totalFragment = externalFrag + sumInternalFrag;

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

    printf("Internal Fragmentation: %d KB\n", sumInternalFrag);
    printf("External Fragmentation: %d KB\n", externalFrag);
    printf("Total Fragmentation: %d KB\n", totalFragment);
}

void bestFit(int blockSize[], int m, int processSize[], int n)
{
    int allocation[n];
    int internalFrag[n];
    bool taken[m];
    for (int i = 0; i < n; i++)
    {
        allocation[i] = -1;
        internalFrag[i] = 0;
    }

    for (int i = 0; i < m; i++)
        taken[i] = false;

    for (int i = 0; i < n; i++)
    {
        int bestIdx = -1;
        for (int j = 0; j < m; j++)
            if (blockSize[j] >= processSize[i] && !taken[j])
                if (bestIdx == -1 || blockSize[j] < blockSize[bestIdx])
                    bestIdx = j;

        if (bestIdx != -1)
        {
            allocation[i] = bestIdx;
            internalFrag[i] = blockSize[bestIdx] - processSize[i];
            blockSize[bestIdx] -= processSize[i];
            taken[bestIdx] = true;
        }
    }

    int externalFrag = 0;
    int sumInternalFrag = 0;
    for (int j = 0; j < m; j++)
    {
        if (!taken[j])
            externalFrag += blockSize[j];
        else
            sumInternalFrag += blockSize[j];
    }
    int totalFragment = externalFrag + sumInternalFrag;

    printf("\nBest Fit:\n");
    printf("Process No.\tProcess Size\tBlock No.\tInternal Fragmentation\n");

    for (int i = 0; i < n; i++)
    {
        printf("%d\t\t%d\t\t", i + 1, processSize[i]);
        if (allocation[i] != -1)
            printf("%d\t\t%d\n", allocation[i] + 1, internalFrag[i]);

        else
            printf("Not Allocated\t-\n");
    }
    printf("Internal Fragmentation: %d KB\n", sumInternalFrag);
    printf("External Fragmentation: %d KB\n", externalFrag);
    printf("Total Fragmentation: %d KB\n", totalFragment);
}

void worstFit(int blockSize[], int m, int processSize[], int n)
{
    int allocation[n];
    int internalFrag[n];
    bool taken[m];
    for (int i = 0; i < n; i++)
    {
        allocation[i] = -1;
        internalFrag[i] = 0;
    }

    for (int i = 0; i < m; i++)
        taken[i] = false;

    for (int i = 0; i < n; i++)
    {
        int worstIdx = -1;
        for (int j = 0; j < m; j++)
            if (blockSize[j] >= processSize[i] && !taken[j])
                if (worstIdx == -1 || blockSize[j] > blockSize[worstIdx])
                    worstIdx = j;

        if (worstIdx != -1)
        {
            allocation[i] = worstIdx;
            internalFrag[i] = blockSize[worstIdx] - processSize[i];
            blockSize[worstIdx] -= processSize[i];
            taken[worstIdx] = true;
        }
    }

    int externalFrag = 0;
    int sumInternalFrag = 0;
    for (int j = 0; j < m; j++)
    {
        if (!taken[j])
            externalFrag += blockSize[j];
        else
            sumInternalFrag += blockSize[j];
    }
    int totalFragment = externalFrag + sumInternalFrag;

    printf("\nWorst Fit:\n");
    printf("Process No.\tProcess Size\tBlock No.\tInternal Fragmentation\n");

    for (int i = 0; i < n; i++)
    {
        printf("%d\t\t%d\t\t", i + 1, processSize[i]);
        if (allocation[i] != -1)
            printf("%d\t\t%d\n", allocation[i] + 1, internalFrag[i]);

        else
            printf("Not Allocated\t-\n");
    }
    printf("Internal Fragmentation: %d KB\n", sumInternalFrag);
    printf("External Fragmentation: %d KB\n", externalFrag);
    printf("Total Fragmentation: %d KB\n", totalFragment);
}

int main()
{
    int blockSize1[] = {150, 350, 400, 200, 300};
    int processSize[] = {300, 200, 400, 150, 100};
    int m = sizeof(blockSize1) / sizeof(blockSize1[0]);
    int n = sizeof(processSize) / sizeof(processSize[0]);

    int blockSize2[m], blockSize3[m];
    for (int i = 0; i < m; i++)
    {
        blockSize2[i] = blockSize1[i];
        blockSize3[i] = blockSize1[i];
    }

    firstFit(blockSize1, m, processSize, n);
    bestFit(blockSize2, m, processSize, n);
    worstFit(blockSize3, m, processSize, n);

    return 0;
}
