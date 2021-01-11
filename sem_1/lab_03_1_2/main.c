#include <stdio.h>
#include <stdlib.h>

#define RESULT_ERROR 3
#define LOGIC_ERROR 2
#define INPUT_ERROR 1
#define OK 0

#define MIN_SIZE 1
#define MAX_N 10
#define MAX_M 10

int get_matrix(int a[MAX_N][MAX_M], int *const n, int *const m)
{
    printf("Input row's number:\n    ");
    if (scanf("%d", n) != 1 || MIN_SIZE > *n || MAX_N < *n)
        return INPUT_ERROR;

    printf("Input column's number:\n    ");
    if (scanf("%d", m) != 1 || MIN_SIZE > *m || MAX_N < *m)
        return INPUT_ERROR;

    printf("Input elements of matrix:\n");
    for (int i = 0; i < *n; i++)
        for (int j = 0; j < *m; j++)
            if (scanf("%d", &a[i][j]) != 1)
                return INPUT_ERROR;

    return OK;
}

int sum_of_numbers(int a)
{
    int sum = 0;
    a = abs(a);
    while (a > 0)
    {
        sum += a % 10;
        a /= 10;
    }
    
    return sum;
}

int remove_cross_of_min_num_sum_el(int a[MAX_N][MAX_M], int *const n, int *const m)
{
    int min = -1; 
    int min_count = 0;
    int min_i = 0, min_j = 0;
    int cur;

    for (int i = 0; i < *n; i++)
        for (int j = 0; j < *m; j++)
        {
            cur = sum_of_numbers(a[i][j]);

            if (cur == min)
                min_count += 1;    

            if (cur < min || -1 == min)
            {
                min = cur;
                min_i = i;
                min_j = j;
                min_count = 0;
            }
        }

    if (min_count)
        return LOGIC_ERROR;

    (*n)--;
    for (int i = min_i; i < *n; i++)
        for (int j = 0; j < *m; j++)
            a[i][j] = a[i + 1][j];
    
    (*m)--;
    for (int i = 0; i < *n; i++)
        for (int j = min_j; j < *m; j++)
            a[i][j] = a[i][j + 1];

    return OK;
}

int print_matrtix(const int a[MAX_N][MAX_M], int n, int m)
{
    if (n == 0 || m == 0)
        return RESULT_ERROR;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            printf("%d ", a[i][j]);

        printf("\n");
    }

    return OK;
}

int main(void)
{
    int matrix[MAX_N][MAX_N];
    
    int n, m;

    if (get_matrix(matrix, &n, &m) != OK)
    {
        printf("Input error found\n");
        return INPUT_ERROR;
    }

    if (remove_cross_of_min_num_sum_el(matrix, &n, &m) != OK)
    {
        printf("There is more then one min elem\n");
        return LOGIC_ERROR;
    }

    printf("\n");

    if (print_matrtix((const int (*)[MAX_N]) matrix, n, m) != OK)
    {
        printf("There is empty result\n");
        return RESULT_ERROR;
    }   

    return OK;
}