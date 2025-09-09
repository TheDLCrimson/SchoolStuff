#include <stdio.h>
#include <stdbool.h>

int main()
{
    int n, i, tq, time = 0, context_switches = 0;
    bool done;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int bt[n], rem_bt[n], at[n], wt[n], tat[n];

    printf("Enter the time quantum: ");
    scanf("%d", &tq);

    printf("Enter burst time and arrival time for each process:\n");
    for (i = 0; i < n; i++)
    {
        printf("P[%d] - Burst Time: ", i + 1);
        scanf("%d", &bt[i]);
        printf("P[%d] - Arrival Time: ", i + 1);
        scanf("%d", &at[i]);
        rem_bt[i] = bt[i];
        wt[i] = 0;
    }

    while (1)
    {
        done = true;

        for (i = 0; i < n; i++)
        {
            if (rem_bt[i] > 0 && at[i] <= time)
            {

                done = false;

                if (rem_bt[i] > tq)
                {
                    time += tq;
                    rem_bt[i] -= tq;

                    context_switches++;

                    for (int j = 0; j < n; j++)
                    {
                        if (j != i && rem_bt[j] > 0 && at[j] <= time)
                            wt[j] += tq;
                    }
                }
                else
                {
                    time += rem_bt[i];
                    rem_bt[i] = 0;

                    wt[i] = time - bt[i] - at[i];

                    context_switches++;
                }
            }
        }

        if (done == true)
            break;
    }

    int total_wt = 0, total_tat = 0;
    for (i = 0; i < n; i++)
    {
        tat[i] = bt[i] + wt[i];
        total_wt += wt[i];
        total_tat += tat[i];
    }

    printf("\nProcess\tBurst Time\tArrival Time\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < n; i++)
    {
        printf("P[%d]\t\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, bt[i], at[i], wt[i], tat[i]);
    }

    printf("\nTotal Context Switches: %d", context_switches);
    printf("\nAverage Waiting Time: %.2f", (float)total_wt / n);
    printf("\nAverage Turnaround Time: %.2f\n", (float)total_tat / n);

    return 0;
}