#include <stdio.h>
#include <stdbool.h>

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

void get_array_of_symmetry(const int a[MAX_N][MAX_M], int n, int m, int * const arr)
{
    bool symmetric;
    for (int i = 0; i < n; i++)
    {
        symmetric = true; 
        for (int j = 0; j < (m + 1) / 2; j++)
            if (a[i][j] != a[i][m - j - 1])
            {
                symmetric = false;
                break;
            }
        *(arr + i) = symmetric;
    }
}

void print_array(const int *const a, int n)
{
    for (int const *i = a; i < a + n; i++)
        printf("%d ", *i);

    printf("\n");
}

int main(void)
{
    int matrix[MAX_N][MAX_N];
    
    int arr_of_symmetry[MAX_N];
    int n, m;

    if (get_matrix(matrix, &n, &m) != OK)
    {
        printf("Input error found\n");
        return INPUT_ERROR;
    }

    get_array_of_symmetry((const int (*)[MAX_N]) matrix, n, m, arr_of_symmetry);

    printf("\n");

    print_array(arr_of_symmetry, n);

    return OK;
}