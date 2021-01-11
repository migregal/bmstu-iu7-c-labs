#include <stdlib.h>
#include <time.h>

#include "my_file.h"

#define OK 0

#define INPUT_ERROR -1
#define FILE_NAME_ERROR -2
#define CLOSING_FILE_ERROR -3

#define DATA_ERROR 1

#define CREATING_FILE_ERROR 2


int file_size(FILE *f, size_t *size)
{
    size_t sz;
    
    if (fseek(f, 0L, SEEK_END))
        return INPUT_ERROR;
    
    sz = ftell(f);
    
    if (sz <= 0)
        return DATA_ERROR;
    
    if (sz % sizeof(int))
        return DATA_ERROR;

    *size = sz / sizeof(int);
    
    return fseek(f, 0L, SEEK_SET);
}

int create_random_nums_file(char *file_name, int file_size)
{
    FILE *fout;

    fout = fopen(file_name, "wb");

    if (fout == NULL)
        return FILE_NAME_ERROR;

    srand(time(NULL));

    int x;
    while (file_size--)
    {
        x = rand();
        fwrite(&x, sizeof(int), 1, fout);
    }
        
    if (fclose(fout) == EOF)
        return CLOSING_FILE_ERROR;

    return OK;
}

int print_file(char *file_name)
{
    FILE *fin;

    fin = fopen(file_name, "rb");

    if (fin == NULL)
        return FILE_NAME_ERROR;

    size_t size;

    if (file_size(fin, &size))
        return DATA_ERROR;
       
    int x;

    while (fread(&x, sizeof(int), 1, fin) == 1)
        printf("%d ", x);
    
    printf("\n");
        
    if (feof(fin) == 0)
    {
        if (fclose(fin) == EOF)
            return CLOSING_FILE_ERROR;

        return DATA_ERROR;
    }
        
    if (fclose(fin) == EOF)
        return CLOSING_FILE_ERROR;

    return OK;
}

int get_number_by_pos(FILE *fin, int pos)
{
    fseek(fin, sizeof(int) * pos, SEEK_SET);

    int x;
    fread(&x, sizeof(int), 1, fin);

    return x;
}

void put_number_by_pos(FILE *fout, int pos, int num)
{
    fseek(fout, sizeof(int) * pos, SEEK_SET);
    fwrite(&num, sizeof(int), 1, fout);
}

size_t new_gap(size_t gap)
{
    gap = gap * 10 / 13;

    if (gap == 9 || gap == 10)
        return 11;

    if (gap < 1)
        return 1;

    return gap;
}

void combsort(FILE* fin, size_t size)
{
    size_t gap = size;

    for (int swapped = 0; ; gap = new_gap(gap), swapped = 0)
    {  
        for (size_t i = 0, j = gap; i < size - gap; i++, j = i + gap)
        {
            int a, b;

            a = get_number_by_pos(fin, i);
            b = get_number_by_pos(fin, j);

            if (a <= b)
                continue;

            put_number_by_pos(fin, i, b);
            put_number_by_pos(fin, j, a);

            swapped = 1;
        }

        if (gap == 1 && !swapped)
            break;
    }
}

int sort_file(char *file_name)
{
    size_t size;

    FILE *fin;

    fin = fopen(file_name, "r+b");

    if (fin == NULL)
        return FILE_NAME_ERROR;

    if (file_size(fin, &size))
    {
        if (fclose(fin) == EOF)
            return CLOSING_FILE_ERROR;

        return DATA_ERROR;
    }
    
    combsort(fin, size);

    if (fclose(fin) == EOF)
        return CLOSING_FILE_ERROR;

    return OK;
}

