#include <stdio.h>
#include <sys/stat.h>

void determineFileSize(const char *filename)
{
    struct stat fileStat;
    if (stat(filename, &fileStat) == 0)
    {
        printf("File size: %ld bytes\n", fileStat.st_size);
    }
    else
    {
        printf("Could not determine file size\n");
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    determineFileSize(argv[1]);
    return 0;
}
