#include <stdio.h>

#define MAX_ARR_LEN 1000

#define OK 0

int get_unique_elems_count(int *array, int size)
{
    int res = 0;

    short unique;
    for (int i = 0; i < size; i++)
    {
        if (array[i] <= 0)
            continue;
        
        unique = 1;

        for (int j = 0; j < size; j++)
            if (j != i && array[i] == array[j])
            {
                unique = 0;
                break;
            }

        if (unique)
            res++;
    }

    return res;
}

int main(void)
{
    int arr[MAX_ARR_LEN];
    int size = 0;

    for (int *i = arr; i < arr + MAX_ARR_LEN && scanf("%d", i) != EOF; i++, size++);

    printf("%d\n", get_unique_elems_count(arr, size));

    return OK;
}