#include <stdio.h>

#define OK 0
#define INPUT_ERROR 1

#define TRUE 1
#define FALSE 0

#define MIN_SIZE 1
#define MAX_SIZE 10

int get_array(int *first, int **aft_last)
{
    unsigned short n;
    printf("Input size of the array:\n    ");
    
    if (scanf("%hu", &n) != 1)
        return FALSE;
    
    if (n <= MIN_SIZE || n > MAX_SIZE)
        return FALSE;
        
    printf("Input array elems:\n    ");

    for (int *i = first; i < first + n ; ++i)
    {
        if (scanf("%d", i) != 1)
            return FALSE;

        *aft_last += 1;
    }
    
    return TRUE;
}

long get_min_pair(int *first, int *aft_last)
{
    int *min = first;
    for (int *i = first; i < aft_last - 1; i++)
        if ((*i) * *(i + 1) < (*min) * *(min + 1) || i == first)
            min = i;

    return (*min) * *(min + 1);
}

int main(void)
{
    int arr[MAX_SIZE];
    int *after_last = arr;

    if (!get_array(arr, &after_last))
    {
        printf("Input error found!\n");
        return INPUT_ERROR;
    }
    
    printf("Result:\n    ");
    printf("%ld\n", get_min_pair(arr, after_last));

    return OK;
}