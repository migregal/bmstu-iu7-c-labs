#include <stdio.h>

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

void x_row_swap(int a[MAX_N][MAX_M], int n, int m)
{
    for (int i = 0; i < (n + 1) / 2; i++)     
        for (int j = i; j < m - i; j++)
        {                
            int temp = a[i][j];
            a[i][j] = a[n - i - 1][j];
            a[n - i - 1][j] = temp;
        }
}

void print_matrtix(const int a[MAX_N][MAX_M], int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            printf("%d ", a[i][j]);

        printf("\n");
    }
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

    if (n != m)
    {
        printf("The matrix must be square\n");
        return LOGIC_ERROR;
    }
    
    x_row_swap(matrix, n, m);

    printf("\n");

    print_matrtix((const int (*)[MAX_N]) matrix, n, m);

    return OK;
}