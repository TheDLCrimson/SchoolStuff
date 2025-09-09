#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int id;
    int bt;
    int wt;
    int tat;
} Process;

int compare(const void *a, const void *b)
{
    return ((Process *)a)->bt - ((Process *)b)->bt;
}

int main()
{
    int n, i;
    int total_wt = 0, total_tat = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process processes[n];

    printf("Enter burst time for each process:\n");
    for (i = 0; i < n; i++)
    {
        processes[i].id = i + 1;
        printf("P[%d]: ", processes[i].id);
        scanf("%d", &processes[i].bt);
    }

    qsort(processes, n, sizeof(Process), compare);

    processes[0].wt = 0;

    for (i = 1; i < n; i++)
    {
        processes[i].wt = processes[i - 1].bt + processes[i - 1].wt;
        total_wt += processes[i].wt;
    }

    for (i = 0; i < n; i++)
    {
        processes[i].tat = processes[i].bt + processes[i].wt;
        total_tat += processes[i].tat;
    }

    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < n; i++)
    {
        printf("P[%d]\t\t%d\t\t%d\t\t%d\n", processes[i].id, processes[i].bt, processes[i].wt, processes[i].tat);
    }

    printf("\nAverage Waiting Time: %.2f", (float)total_wt / n);
    printf("\nAverage Turnaround Time: %.2f\n", (float)total_tat / n);

    return 0;
}