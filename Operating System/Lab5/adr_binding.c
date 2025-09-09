#include <stdio.h>
int globalVar = 42; // Global variable
int main()
{
    int localVar = 10; // Local variable
    printf("Value of globalVar: %d\n", globalVar);
    printf("Value of localVar: %d\n", localVar);
    return 0;
}
