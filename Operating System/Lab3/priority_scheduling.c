#include <stdio.h>

int main()
{
    int n, i, j, temp;
    int bt[20], wt[20], tat[20], pr[20], p[20];
    int total_wt = 0, total_tat = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter burst time and priority for each process:\n");
    for (i = 0; i < n; i++)
    {
        printf("P[%d] - Burst Time: ", i + 1);
        scanf("%d", &bt[i]);
        printf("P[%d] - Priority: ", i + 1);
        scanf("%d", &pr[i]);
        p[i] = i + 1;
    }

    // Sort processes by priority
    for (i = 0; i < n - 1; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (pr[i] < pr[j])
            {
                temp = pr[i];
                pr[i] = pr[j];
                pr[j] = temp;

                temp = bt[i];
                bt[i] = bt[j];
                bt[j] = temp;

                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    wt[0] = 0;

    // Calculate waiting time
    for (i = 1; i < n; i++)
    {
        wt[i] = bt[i - 1] + wt[i - 1];
        total_wt += wt[i];
    }

    // Calculate turnaround time
    for (i = 0; i < n; i++)
    {
        tat[i] = bt[i] + wt[i];
        total_tat += tat[i];
    }

    printf("\nProcess\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < n; i++)
    {
        printf("P[%d]\t\t%d\t\t%d\t\t%d\t\t%d\n", p[i], bt[i], pr[i], wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time: %.2f", (float)total_wt / n);
    printf("\nAverage Turnaround Time: %.2f\n", (float)total_tat / n);

    return 0;
}