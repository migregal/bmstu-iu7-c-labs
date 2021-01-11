#include <stdio.h>

#define OK 0
#define DATA_ERROR 1
#define INPUT_ERROR 2

#define TRUE 1
#define FALSE 0

#define MIN_SIZE 1
#define MAX_SIZE 10

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

long long product_of_odd_elements(const int arr[], int n)
{
    long long prod = 0;

    for (int i = 0; i < n; i++)
    {
        if (arr[i] % 2 != 0)
        {
            (!(prod) && (prod = 1));
            prod *= arr[i];
        }
    }

    return prod;
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

    long long res = product_of_odd_elements(arr, n);
    
    if (!res)
    {
        printf("There isn't odd elems in array!\n");   
        return DATA_ERROR;
    }

    printf("Result:\n    %lld\n", res);
    return OK;
}
