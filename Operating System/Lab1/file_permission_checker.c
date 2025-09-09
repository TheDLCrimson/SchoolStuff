#include <stdio.h>
#include <sys/stat.h>

void checkPermissions(const char *filename)
{
    struct stat fileStat;
    if (stat(filename, &fileStat) == 0)
    {
        printf("Permissions: %o\n", fileStat.st_mode & 0777);
    }
    else
    {
        printf("Could not check permissions\n");
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    checkPermissions(argv[1]);
    return 0;
}
