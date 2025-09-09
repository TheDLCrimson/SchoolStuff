#include <stdio.h>

int main()
{
    int n, i;
    int burst_time[20], wait_time[20], tat[20];
    int total_wt = 0, total_tat = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter burst time for each process:\n");
    for (i = 0; i < n; i++)
    {
        printf("P[%d]: ", i + 1);
        scanf("%d", &burst_time[i]);
    }

    wait_time[0] = 0; // Waiting time for the first process is 0

    // Calculate waiting time
    for (i = 1; i < n; i++)
    {
        wait_time[i] = burst_time[i - 1] + wait_time[i - 1];
        total_wt += wait_time[i];
    }

    // Calculate turnaround time
    for (i = 0; i < n; i++)
    {
        tat[i] = burst_time[i] + wait_time[i];
        total_tat += tat[i];
    }

    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < n; i++)
    {
        printf("P[%d]\t\t%d\t\t%d\t\t%d\n", i + 1, burst_time[i], wait_time[i], tat[i]);
    }

    printf("\nAverage Waiting Time: %.2f", (float)total_wt / n);
    printf("\nAverage Turnaround Time: %.2f\n", (float)total_tat / n);

    return 0;
}