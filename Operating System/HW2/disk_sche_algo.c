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
