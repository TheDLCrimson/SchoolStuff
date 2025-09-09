#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int fd;
    char *buffer;
    int buffer_size = 69;
    ssize_t bytes_read;

    buffer = (char *)malloc(buffer_size * sizeof(char));
    if (buffer == NULL)
    {
        printf("Memory allocation failed!\n");
        return 1;
    }

    fd = open("testfile.txt", O_CREAT | O_WRONLY, 0755);
    if (fd == -1)
    {
        printf("Error opening file!\n");
        return 1;
    }
    write(fd, "Hello, Kieu Hai Dang is the best TA!\n\n\nPlease give me good grades.\n", 69);
    close(fd);

    fd = open("testfile.txt", O_RDONLY);
    if (fd == -1)
    {
        printf("Error opening file!\n");
        return 1;
    }
    while ((bytes_read = read(fd, buffer, buffer_size - 1)) > 0)
    {
        buffer[bytes_read] = '\0';
        printf("%s", buffer);
    }

    close(fd);

    free(buffer);

    return 0;
}
