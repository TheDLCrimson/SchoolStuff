#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, init_head, total_seek = 0;
    printf("NMax range of disk: ");
    scanf("%d", &n);

    printf("Size of queue request: ");
    scanf("%d", &n);

    int *requests = malloc(n * sizeof(int));

    printf("Queue of disk positions to be read: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &requests[i]);

    printf("Init head position: ");
    scanf("%d", &init_head);

    printf("\n");
    int curr_position = init_head;

    for (int i = 0; i < n; i++)
    {
        int seek = abs(curr_position - requests[i]);
        total_seek += seek;
        printf("Disk head moves from %d to %d with seek %d\n", curr_position, requests[i], seek);
        curr_position = requests[i];
    }

    printf("Total seek time is %d\n", total_seek);
    printf("Average seek time is %.6f\n", (double)total_seek / n);

    free(requests);
    return 0;
}
