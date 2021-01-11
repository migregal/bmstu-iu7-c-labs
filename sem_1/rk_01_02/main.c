#include <stdio.h>

#define OK 0
#define LOGIC_ERROR 1

#define MAX_ROW_COUNT 1000
#define MAX_COLL_COUNT 10

int add_num_to_arr(int x, int *arr)
{
    int len = 0;

    while (x > 0)
    {
        len++;

        for (int i = len; i > 0; i--)
            arr[i] = arr[i - 1];
        
        arr[0] = x % 10;

        x /= 10;
    }

    for (int i = len; i < MAX_COLL_COUNT; i++)
        arr[i] = -1;
    
    return len > 0;
}

int get_num(int array[MAX_COLL_COUNT])
{
    int res = 0, ind = 1;

    for (int i = MAX_COLL_COUNT - 1; i >= 0; i--)
    {
        if (array[i] == -1)
            continue;
        
        res = array[i] * ind + res;
        ind *= 10;
    }
    return res;
}

int is_even(int arr[MAX_COLL_COUNT])
{
    int i = 0;
    for (; i < MAX_COLL_COUNT; i++)
    {
        if (i == MAX_COLL_COUNT - 1)
            break;

        if (arr[i] == -1)
        {
            i--;
            break;
        }
    }
        
            
    return arr[i] % 2 == 0;
}

int get_len(int arr[MAX_COLL_COUNT])
{
    int i = 0;

    for(; i < MAX_COLL_COUNT && arr[i] != -1; i++);
    
    return i;
}

int compare_arr(int arr1[MAX_COLL_COUNT], int arr2[MAX_COLL_COUNT])
{
    if (get_len(arr1) > get_len(arr2))
        return 1;

    if (get_len(arr1) < get_len(arr2))
        return -1;

    for (int i = 0; i < MAX_COLL_COUNT; i++)
    {
        if (arr1[i] > arr2[i])
            return 1;
        
        if (arr1[i] < arr2[i])
            return -1;
    }

    return 0;
}

int get_min_num_row(int matrix[MAX_ROW_COUNT][MAX_COLL_COUNT], int size)
{
    int res = 0;
    for (int i = 1; i < size; i++){

        if (compare_arr(matrix[res], matrix[i]) > 0 && is_even(matrix[i]))
            res = i;
    }
    return is_even(matrix[res]) ? res : -1;
}

int main(void)
{
    int matrix[MAX_ROW_COUNT][MAX_COLL_COUNT];

    int size = 0, x;

    while (scanf("%d", &x) != EOF)
        size += add_num_to_arr(x, matrix[size]);

    int min_row = get_min_num_row(matrix, size);

    if (min_row < 0)
        return LOGIC_ERROR;

    printf("min even number %d\n", get_num(matrix[min_row]));

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < MAX_COLL_COUNT && matrix[i][j] != -1; j++)
            printf("%d ", matrix[i][j]);

        printf("\n");
    }

    return OK;
}