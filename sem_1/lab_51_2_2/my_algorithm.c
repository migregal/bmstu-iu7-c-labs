#include <math.h>
#include "my_algorithm.h"

#define OK 0
#define INPUT_ERROR -1
#define SIZE_ERROR -2

#define DOUBLE_EPS 1e-6

size_t file_size(FILE *f, size_t *size)
{
    long start, sz;
    
    start = ftell(f);

    if (fseek(f, 0L, SEEK_END))
        return INPUT_ERROR;
    
    sz = ftell(f);
    
    if (sz <= 0)
        return INPUT_ERROR;
    
    *size = sz;
    
    return fseek(f, start, SEEK_SET);
}

int get_average_num(FILE * f, double *const avg)
{
    size_t size;
    
    if (file_size(f, &size) != 0)
        return INPUT_ERROR;

    double sum = 0;
    double x;
    int count = 0;

    while (fscanf(f, "%lf", &x) == 1 && ++count)
        sum += x;

    if (feof(f) == 0)
        return INPUT_ERROR;

    fseek(f, 0L, SEEK_SET);

    *avg = 0;
    
    if (count != 0)
        *avg = sum / count;

    return OK;
}

int get_nums_disp(FILE *f, const double avg, double *res)
{
    size_t size;

    if (file_size(f, &size) != 0)
        return INPUT_ERROR;
    
    double disp = 0, x;
    int count = 0;

    while (fscanf(f, "%lf", &x) == 1)
    {
        disp += (x - avg) * (x - avg);
        count++;
    }
        
    disp /= count;
    
    if (feof(f) == 0)
        return INPUT_ERROR;

    *res = disp;
    
    return OK;
}