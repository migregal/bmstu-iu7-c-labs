#include <stdio.h>
#include <stdlib.h>

#define INPUT_ERROR 1
#define DATA_ERROR 2
#define OK 0

#define MIN_SIZE 1
#define MAX_N 10
#define MAX_M 10

#define BORDER 10
#define ROTATE_SIZE 3

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

void array_rotate_left(int *const arr, int size, int pos)
{
    pos %= size;
    int j, temp;

    for (int i = 0; i < (size - 1) * pos; i++)
    {
        j = i % (size - 1);
        temp = *(arr + j);
        *(arr + j) = *(arr + j + 1);
        *(arr + j + 1) = temp;
    }
}

void array_rotate_right(int *const arr, int size, int pos)
{
    pos %= size;
    int j, temp;

    for (int i = (size - 1) * pos; i > 0; i--)
    {
        j = (i - 1) % (size - 1) + 1;
        temp = *(arr + j);
        *(arr + j) = *(arr + j - 1);
        *(arr + j - 1) = temp;
    }
}

int rotate_10_s_elems_in_circle(int a[MAX_N][MAX_M], int n, int m, int rotate)
{
    int arr[MAX_N * MAX_M];
    int arr_len = 0;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (sum_of_numbers(a[i][j]) > BORDER)
                arr[arr_len++] = a[i][j];
    
    if (!arr_len)
        return DATA_ERROR;

    if (rotate > 0)
        array_rotate_left(arr, arr_len, rotate);
    else
        array_rotate_right(arr, arr_len, abs(rotate));
    

    arr_len = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (sum_of_numbers(a[i][j]) > BORDER)
                a[i][j] = arr[arr_len++];

    return OK;
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

    short res_code = OK;

    res_code = get_matrix(matrix, &n, &m);
    if (res_code)
        return res_code;

    res_code = rotate_10_s_elems_in_circle(matrix, n, m, ROTATE_SIZE);
    if (res_code)
        return res_code;

    printf("\n");

    print_matrtix((const int (*)[MAX_N]) matrix, n, m);

    return OK;
}