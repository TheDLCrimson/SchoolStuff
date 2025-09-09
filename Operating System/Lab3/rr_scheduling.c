#include <stdio.h>
int main()
{
    int n, i, tq, count = 0, temp, sq = 0;
    int burst_time[10], rem_bt[10], wait_time[10], tat[10];
    float avg_wt = 0, avg_tat = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the time quantum: ");
    scanf("%d", &tq);
    printf("Enter burst time for each process:\n");

    for (i = 0; i < n; i++)
    {
        printf("P[%d]: ", i + 1);
        scanf("%d", &burst_time[i]);
        rem_bt[i] = burst_time[i];
    }
    while (1)
    {
        int done = 1;
        for (i = 0; i < n; i++)
        {
            if (rem_bt[i] > 0)
            {
                done = 0; // There is a pending process
                if (rem_bt[i] > tq)
                {
                    sq += tq;
                    rem_bt[i] -= tq;
                }
                else
                {
                    sq += rem_bt[i];
                    wait_time[i] = sq - burst_time[i];
                    rem_bt[i] = 0;
                }
            }
        }
        if (done == 1)
            break;
    }

    for (i = 0; i < n; i++)
    {
        tat[i] = burst_time[i] + wait_time[i];
        avg_wt += wait_time[i];
        avg_tat += tat[i];
    }

    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");

    for (i = 0; i < n; i++)
    {
        printf("P[%d]\t\t%d\t\t%d\t\t%d\n", i + 1, burst_time[i], wait_time[i], tat[i]);
    }

    printf("\nAverage Waiting Time: %.2f", avg_wt / n);
    printf("\nAverage Turnaround Time: %.2f\n", avg_tat / n);

    return 0;
}