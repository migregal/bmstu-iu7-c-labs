#include <stdio.h>

#define OK 0
#define INPUT_ERROR 1

#define TRUE 1
#define FALSE 0

#define MIN_SIZE 0
#define MAX_SIZE 1000000

int get_array(int arr[], int *n)
{
    printf("Input size of the array:\n    ");
    
    if (scanf("%d", n) != 1)
        return FALSE;
    
    if (*n <= MIN_SIZE || *n > MAX_SIZE)
        return FALSE;

    printf("Input array elems:\n    ");
    
    for (int i = 0; i < *n; ++i)
        if (scanf("%d", &arr[i]) != 1)
            return FALSE;
    
    return TRUE;
}

void inserts_sort(int arr[], int n)
{
    for (int *i = arr + 1; i < arr + n; ++i)
    {
        for (int *j = i; j > arr && *(j - 1) > *j; j--)
        {
            int tmp = *(j - 1);
            *(j - 1) = *j;
            *j = tmp;
        }
    }
}

void print_res(int a[], int n)
{
    printf("Result:\n");

    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);

    printf("\n");
}

int main(void)
{
    int n;
    int arr[MAX_SIZE];
    
    if (!get_array(arr, &n))
    {
        printf("Input error found!\n");
        return INPUT_ERROR;
    }
    
    inserts_sort(arr, n);
    print_res(arr, n);
    return OK;
}