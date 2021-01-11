#include <stdio.h>

#define OK 0
#define DATA_ERROR 1
#define INPUT_ERROR 2
#define LOGIC_ERR -1

#define TRUE 1
#define FALSE 0

#define MIN_SIZE 1
#define MAX_SIZE 10

#define MIN_N 0
#define MAX_N 92

int get_array(int arr[], int *n)
{
    printf("Input size of the array:\n    ");

    if (scanf("%d", n) != 1)
        return FALSE;
    
    if (*n < MIN_SIZE || *n > MAX_SIZE)
        return FALSE;
        
    printf("Input array elems:\n    ");
    
    for (int i = 0; i < *n; ++i)
        if (scanf("%d", &arr[i]) != 1)
            return FALSE;
    
    return TRUE;
}

int fib(short n)
{
    long long int f0 = 0, f1 = 1;

    if (n < MIN_N || n > MAX_N)
        return LOGIC_ERR;

    if (n <= 1)
        return n;

    for (int i = 2; i <= n; i++)
    {
        f1 += f0;
        f0 = f1 - f0;
    }

    return f1;
}

unsigned insert_fib_elements(int arr[], int *n)
{
    for (int i = 0, ins_c = 0; i < *n; i++)
    {
        if (arr[i] % 3 != 0)
            continue;

        for (int j = (*n)++; j > i + 1; j--)
            arr[j] = arr[j - 1];
            
        arr[++i] = fib(ins_c++);

        if (arr[i] == LOGIC_ERR)
            return FALSE;
    }

    return TRUE;
}

void print_res(const int a[], int n)
{
    printf("Result:\n    ");

    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    
    printf("\n");
}

int main(void)
{
    int n;
    int arr[2 * MAX_SIZE];
    
    if (!get_array(arr, &n))
    {
        printf("Input error found!\n");
        return INPUT_ERROR;
    }

    if (!insert_fib_elements(arr, &n))
    {
        printf("There isn't elems divided by 3 in array!\n");
        return DATA_ERROR;
    }

    print_res(arr, n);
    return OK;
}