#include <stdlib.h>
#include <stdio.h>
#include "utils.h"

int main()
{
    int* x = opaque((char*)malloc(100) + 1);
    *(int*)opaque(x) = 42;
    printf("x = %d\n", *x);
    return 0;
}

