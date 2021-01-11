#include <stdio.h>

#define OK 0
#define DATA_ERROR 1
#define INPUT_ERROR 2

#define TRUE 1
#define FALSE 0

#define MIN_SIZE 1
#define MAX_SIZE 10

short get_array(long arr[], unsigned short *n)
{
    printf("Input size of the array:\n    ");
    
    if (scanf("%hu", n) != 1)
        return FALSE;
    
    if (*n < MIN_SIZE|| *n > MAX_SIZE)
        return FALSE;

    printf("Input array elems:\n    ");
    
    for (int i = 0; i < *n; ++i)
        if (scanf("%ld", &arr[i]) != 1)
            return FALSE;
    
    return TRUE;
}

short is_prime(long x)
{        
    if (x < 2)
        return FALSE;
        
    int div = 2;
    while (div * div <= x)
    {
        if (x % div == 0)
            return FALSE;
            
        div++;
    }

    return TRUE;
}

unsigned short found_prime_elements(const long a[], long b[], unsigned short n, unsigned short m)
{
    unsigned short count = 0;

    for (int i = 0; i < n; i++)
    {
        if (is_prime(a[i]))
        {
            if (count < m)
                b[count++] = a[i];
            else
                break;
        }
    }

    return count;
}

void print_res(const long a[], int n)
{
    printf("Result:\n");

    for (int i = 0; i < n; i++)
        printf("%ld ", a[i]);
    
    printf("\n");
}

int main(void)
{
    unsigned short n;
    long arr[MAX_SIZE];
    
    if (!get_array(arr, &n))
    {
        printf("Input error found!\n");
        return INPUT_ERROR;
    }
    
    long res[MAX_SIZE];
    unsigned short res_count = found_prime_elements(arr, res, n, n);

    if (!res_count)
    {
        printf("There isn't simple elems in array!\n");   
        return DATA_ERROR;
    }

    print_res(res, res_count);

    return OK;
}
