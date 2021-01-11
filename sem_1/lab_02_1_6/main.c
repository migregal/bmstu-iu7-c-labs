#include <stdio.h>
#include <stdlib.h>

#include <inttypes.h>
#include <sys/time.h>
#include <time.h>

#define OK 0

#define MAX_ABS_NUMBER_SIZE 50000
#define MCS_IN_A_SECOND 1000000LL

void get_array(int arr[], int n)
{
    for (int i = 0; i < n ; ++i)
    {
        arr[i] = rand() % MAX_ABS_NUMBER_SIZE;
    }
}

void int_array_copy(int dst[], const int src[], size_t size)
{
    while (size--)
        *dst++ = *src++;
}

void get_min_pair_arr_mechs(int a[], int n)
{
    long long min = 0;
    for (int i = 1; i < n; i++)
    {
        if (a[i - 1] * a[i] < min || i == 1)
        {
            min = a[i - 1] * a[i];
        }
    }
}

void get_min_pair_arr_ptr_mechs(int *a, int n)
{
    long long min = 0;
    for (int i = 1; i < n; i++)
    {
        if (*(a + i - 1) * *(a + i) < min || i == 1)
        {
            min = *(a + i - 1) * *(a + i);
        }
    }
}

void get_min_pair_ptr_mechs(int *first, int *after_last)
{
    long long min = 0;
    for (int *i = first; i < after_last - 1; i++)
    {
        if ((*i) * (*(i + 1)) < min || i == first)
        {
            min = (*i) * (*(i + 1));
        }
    }
}

void get_run_time_to_compare(int iters, int size, double *time1, double *time2, double *time3)
{
    srand(time(0));

    struct timeval tv_start, tv_stop;
    int64_t elapsed_time1, elapsed_time2, elapsed_time3;

    elapsed_time1 = 0;
    elapsed_time2 = 0;
    elapsed_time3 = 0;

    for (int i = 0; i < iters; ++i)
    {
        int a[size];
        get_array(a, size);

        int nb = size;
        int b[nb];

        int_array_copy(b, a, nb);
        nb = size;

        gettimeofday(&tv_start, NULL);
        get_min_pair_arr_mechs(b, nb);
        gettimeofday(&tv_stop, NULL);

        elapsed_time1 += 
            (tv_stop.tv_sec - tv_start.tv_sec) * MCS_IN_A_SECOND + 
            (tv_stop.tv_usec - tv_start.tv_usec);

        int_array_copy(b, a, nb);
        nb = size;

        gettimeofday(&tv_start, NULL);
        get_min_pair_arr_ptr_mechs(b, nb);
        gettimeofday(&tv_stop, NULL);

        elapsed_time2 += 
            (tv_stop.tv_sec - tv_start.tv_sec) * MCS_IN_A_SECOND +
            (tv_stop.tv_usec - tv_start.tv_usec);

        int_array_copy(b, a, nb);
        nb = size;

        gettimeofday(&tv_start, NULL);
        get_min_pair_ptr_mechs(b, &b[nb]);
        gettimeofday(&tv_stop, NULL);

        elapsed_time3 += 
            (tv_stop.tv_sec - tv_start.tv_sec) * MCS_IN_A_SECOND +
            (tv_stop.tv_usec - tv_start.tv_usec);
    }

    *time1 = elapsed_time1 / iters;
    *time2 = elapsed_time2 / iters;
    *time3 = elapsed_time3 / iters;
}

int main(void)
{
    int iters, na;

    printf("Input iterations number:\n    ");
    scanf("%d", &iters);


    printf("Input array size:\n    ");
    scanf("%d", &na);

    double time1, time2, time3;

    get_run_time_to_compare(iters, na, &time1, &time2, &time3);

    printf("proc1:\n    %lf\n", time1);
    printf("proc2:\n    %lf\n", time2);
    printf("proc3:\n    %lf\n", time3);

    return OK;
}
