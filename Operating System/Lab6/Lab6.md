##### V202200664 - Luu Nguyen Chi Duc

# Operating System Lab6

## Part A - Theory Questions


    
## Part B - Programing

### Implementing Disk-Scheduling Algorithms

**Code `disk_sche_algo.c`:**

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_CYLINDER 4999
#define NUM_REQUESTS 1000

int compare(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

int find_start_index(int *arr, int len, int head)
{
    int left = 0, right = len - 1, mid;
    while (left <= right)
    {
        mid = left + (right - left) / 2;
        if (arr[mid] == head)
            return mid;
        else if (arr[mid] < head)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return left;
}

void generate_random_requests(int *requests, int num_requests)
{
    srand(time(NULL));
    for (int i = 0; i < num_requests; i++)
        requests[i] = rand() % (MAX_CYLINDER + 1);
}

void read_requests_from_file(char *filename, int *requests, int *num_requests)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        fprintf(stderr, "Error opening file: %s\n", filename);
        exit(1);
    }

    int i = 0;
    while (fscanf(file, "%d,", &requests[i]) != EOF && i < NUM_REQUESTS)
        i++;

    *num_requests = i;
    fclose(file);
}

void scan(int *requests, int num_requests, int head)
{
    qsort(requests, num_requests, sizeof(int), compare);
    int total_movement = 0;
    int start_index = find_start_index(requests, num_requests, head);
    int curr_position = head;
    int seek;

    // Move left
    for (int i = start_index - 1; i >= 0; i--)
    {
        seek = abs(curr_position - requests[i]);
        total_movement += seek;
        curr_position = requests[i];
        printf("Disk head moves from %d to %d with seek %d\n", curr_position, requests[i], seek);
    }

    // Move to the beginning
    seek = abs(curr_position);
    total_movement += seek;
    printf("Disk head moves from %d to %d with seek %d\n", curr_position, 0, seek);
    curr_position = 0;

    // Move right
    for (int i = start_index; i < num_requests; i++)
    {
        seek = abs(curr_position - requests[i]);
        total_movement += seek;
        curr_position = requests[i];
        printf("Disk head moves from %d to %d with seek %d\n", curr_position, requests[i], seek);
    }

    printf("SCAN Total Head Movement: %d cylinders\n", total_movement);
}

void c_scan(int *requests, int num_requests, int head)
{
    qsort(requests, num_requests, sizeof(int), compare);
    int total_movement = 0;
    int start_index = find_start_index(requests, num_requests, head);
    int curr_position = head;
    int seek;

    // Move right
    for (int i = start_index; i < num_requests; i++)
    {
        seek = abs(curr_position - requests[i]);
        total_movement += seek;
        curr_position = requests[i];
        printf("Disk head moves from %d to %d with seek %d\n", curr_position, requests[i], seek);
    }

    // Jump to the beginning
    seek = (MAX_CYLINDER - curr_position) + MAX_CYLINDER;
    total_movement += seek;
    printf("Disk head moves from %d to %d then to %d with seek %d\n", curr_position, MAX_CYLINDER, 0, seek);
    curr_position = 0;

    // Continue
    for (int i = 0; i < start_index; i++)
    {
        seek = abs(curr_position - requests[i]);
        total_movement += seek;
        curr_position = requests[i];
        printf("Disk head moves from %d to %d with seek %d\n", curr_position, requests[i], seek);
    }

    printf("C-SCAN Total Head Movement: %d cylinders\n", total_movement);
}

void c_look(int *requests, int num_requests, int head)
{
    qsort(requests, num_requests, sizeof(int), compare);
    int total_movement = 0;
    int start_index = find_start_index(requests, num_requests, head);
    int curr_position = head;
    int seek;

    // Move right
    for (int i = start_index; i < num_requests; i++)
    {
        seek = abs(curr_position - requests[i]);
        total_movement += seek;
        curr_position = requests[i];
        printf("Disk head moves from %d to %d with seek %d\n", curr_position, requests[i], seek);
    }

    // Jump to the furthest request at the left side
    seek = abs(curr_position - requests[0]);
    total_movement += seek;
    printf("Disk head moves from %d to %d with seek %d\n", curr_position, requests[0], seek);
    curr_position = requests[0];

    // Continue
    for (int i = 0; i < start_index; i++)
    {
        seek = abs(curr_position - requests[i]);
        total_movement += seek;
        curr_position = requests[i];
        printf("Disk head moves from %d to %d with seek %d\n", curr_position, requests[i], seek);
    }

    printf("C-LOOK Total Head Movement: %d cylinders\n", total_movement);
}

int main(int argc, char *argv[])
{
    int head_position;
    int requests[NUM_REQUESTS];
    int num_requests = NUM_REQUESTS;

    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <head_position> [series.txt]\n", argv[0]);
        return 1;
    }

    head_position = atoi(argv[1]);

    if (argc == 3)
        read_requests_from_file(argv[2], requests, &num_requests);
    else
        generate_random_requests(requests, num_requests);

    scan(requests, num_requests, head_position);
    c_scan(requests, num_requests, head_position);
    c_look(requests, num_requests, head_position);

    return 0;
}
```

**Output:**

    PS D:\Code\HWTasks\Operating System\HW2> gcc disk_sche_algo.c -o disk_sche_algo
    PS D:\Code\HWTasks\Operating System\HW2> ./disk_sche_algo 2150 series.txt
    Disk head moves from 2069 to 2069 with seek 81
    Disk head moves from 1618 to 1618 with seek 451
    Disk head moves from 1523 to 1523 with seek 95
    Disk head moves from 1212 to 1212 with seek 311
    Disk head moves from 544 to 544 with seek 668
    Disk head moves from 356 to 356 with seek 188
    Disk head moves from 356 to 0 with seek 356
    Disk head moves from 2296 to 2296 with seek 2296
    Disk head moves from 2800 to 2800 with seek 504
    Disk head moves from 3681 to 3681 with seek 881
    Disk head moves from 4965 to 4965 with seek 1284
    SCAN Total Head Movement: 7115 cylinders
    Disk head moves from 2296 to 2296 with seek 146
    Disk head moves from 2800 to 2800 with seek 504
    Disk head moves from 3681 to 3681 with seek 881
    Disk head moves from 4965 to 4965 with seek 1284
    Disk head moves from 4965 to 4999 then to 0 with seek 5033
    Disk head moves from 356 to 356 with seek 356
    Disk head moves from 544 to 544 with seek 188
    Disk head moves from 1212 to 1212 with seek 668
    Disk head moves from 1523 to 1523 with seek 311
    Disk head moves from 1618 to 1618 with seek 95
    Disk head moves from 2069 to 2069 with seek 451
    C-SCAN Total Head Movement: 9917 cylinders
    Disk head moves from 2296 to 2296 with seek 146
    Disk head moves from 2800 to 2800 with seek 504
    Disk head moves from 3681 to 3681 with seek 881
    Disk head moves from 4965 to 4965 with seek 1284
    Disk head moves from 4965 to 356 with seek 4609
    Disk head moves from 356 to 356 with seek 0
    Disk head moves from 544 to 544 with seek 188
    Disk head moves from 1212 to 1212 with seek 668
    Disk head moves from 1523 to 1523 with seek 311
    Disk head moves from 1618 to 1618 with seek 95
    Disk head moves from 2069 to 2069 with seek 451
    C-LOOK Total Head Movement: 9137 cylinders

### FCFS algorithm

**Code `fcfs.c`:**

```c
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

```

**Output:**

    PS D:\Code\HWTasks\Operating System> cd "d:\Code\HWTasks\Operating System\HW2\" ; if ($?) { gcc fcfs.c -o fcfs } ; if ($?) { .\fcfs }
    NMax range of disk: 200
    Size of queue request: 10
    Queue of disk positions to be read: 12 34 65 78 22 55 87 97 98 75
    Init head position: 50

    Disk head moves from 50 to 12 with seek 38
    Disk head moves from 12 to 34 with seek 22
    Disk head moves from 34 to 65 with seek 31
    Disk head moves from 65 to 78 with seek 13
    Disk head moves from 78 to 22 with seek 56
    Disk head moves from 22 to 55 with seek 33
    Disk head moves from 55 to 87 with seek 32
    Disk head moves from 87 to 97 with seek 10
    Disk head moves from 97 to 98 with seek 1
    Disk head moves from 98 to 75 with seek 23
    Total seek time is 259
    Average seek time is 25.900000
