#include "my_algorithm.h"

#define OK 0
#define INPUT_ERROR -1

int process(FILE *f, int *res)
{
    *res = 0;

    int a, b, c;

    if (fscanf(f, "%d %d %d", &a, &b, &c) != 3)
        return INPUT_ERROR;

    do 
    {
        *res += (a < b && b > c);
        a = b;
        b = c;
    } while (fscanf(f, "%d", &c) == 1);
        

    return OK;
}