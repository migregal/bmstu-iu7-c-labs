#include <stdio.h>

#include "my_algorithm.h"

#define OK 0
#define INPUT_ERROR 1

int main(void)
{
    int result;
    
    if (process(stdin, &result) < 0)
        return INPUT_ERROR;

    printf("%d\n", result);

    return OK;
}