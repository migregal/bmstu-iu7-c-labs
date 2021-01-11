#include <stdio.h>

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

void swap(int *const a, int *const b)
{
    int temp = *a; 
    *a = *b;
    *b = temp;
}

void rows_swap(int *const a, int *const b, int n)
{
    for (int k = 0; k < n; k++)
        swap((a + k), (b + k));
}

void sort_matrix_by_max_elem_desc(int a[MAX_N][MAX_M], int n, int m)
{
    int max_elems[n];
    int max;
    for (int i = 0; i < n; i++)
    {
        max = a[i][0];
        for (int j = 0; j < m; j++)
            if (a[i][j] > max)
                max = a[i][j];

        max_elems[i] = max;
    }

    for (int i = 1; i < n; i++)     
        for (int j = i; j > 0 && max_elems[j - 1] < max_elems[j]; j--)
        {    
            swap(&max_elems[j], &max_elems[j - 1]);
            rows_swap(a[j], a[j - 1], m);
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

    sort_matrix_by_max_elem_desc(matrix, n, m);

    printf("\n");

    print_matrtix((const int (*)[MAX_N]) matrix, n, m);

    return OK;
}