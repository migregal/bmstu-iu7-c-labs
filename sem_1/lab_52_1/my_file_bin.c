#include <stdio.h>

#include <unistd.h>

#include <stdint.h>
#include <string.h>
#include "my_file.h"

#define OK 0
#define FILE_NAME_ERROR 1
#define DATA_ERROR 2

struct student
{
    char second_name[26];
    char first_name[11];
    uint32_t marks[4];
};

int file_size_bin(FILE *f, size_t *size)
{
    size_t sz;
    
    if (fseek(f, 0L, SEEK_END))
        return 1;
    
    sz = ftell(f);
    
    if (sz <= 0)
        return DATA_ERROR;
    
    if (sz % sizeof(struct student))
        return DATA_ERROR;

    *size = sz / sizeof(struct student);
    
    return fseek(f, 0L, SEEK_SET);
}

void get_student_by_pos(FILE *fin, int pos, struct student *stud)
{
    fseek(fin, sizeof(struct student) * pos, SEEK_SET);
    fread(stud, sizeof(struct student), 1, fin);
}

void put_student_by_pos(FILE *fout, int pos, struct student stud)
{
    fseek(fout, sizeof(struct student) * pos, SEEK_SET);
    fwrite(&stud, sizeof(struct student), 1, fout);
}

int find_in_file_bin(char *file_in, char *file_out, char *substr)
{
    FILE *fin;

    fin = fopen(file_in, "rb");

    if (fin == NULL)
        return FILE_NAME_ERROR;

    size_t size = 0;
    
    if (file_size_bin(fin, &size))
    {
        fclose(fin);

        return DATA_ERROR;
    }

    FILE *fout;
    fout = fopen(file_out, "w");

    int k = 0;
    for (int i = 0; i < size; i++)
    {
        struct student temp;
        
        get_student_by_pos(fin, i, &temp);

        if (strstr(temp.second_name, substr) != temp.second_name)
            continue;

        put_student_by_pos(fout, k++, temp);
    }

    fclose(fout);
    fclose(fin);

    if (k == 0)
    {
        remove(file_out);
        return DATA_ERROR;
    }
    
    return OK;
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

void combsort_bin(FILE* fin, size_t size)
{
    size_t gap = size;

    for (int swapped = 0; ; gap = new_gap(gap), swapped = 0)
    {  
        for (size_t i = 0, j = gap; i < size - gap; i++, j = i + gap)
        {
            struct student a, b;

            get_student_by_pos(fin, i, &a);
            get_student_by_pos(fin, j, &b);

            if (strcmp(a.second_name, b.second_name) < 0)
                continue;

            if (strcmp(a.second_name, b.second_name) == 0 && 
                strcmp(a.first_name, b.first_name) <= 0)
                continue;

            put_student_by_pos(fin, i, b);
            put_student_by_pos(fin, j, a);

            swapped = 1;
        }

        if (gap == 1 && !swapped)
            break;
    }
}

int sort_file_bin(char *file_name)
{
    FILE *f;

    f = fopen(file_name, "r+b");

    if (f == NULL)
        return FILE_NAME_ERROR;

    size_t size;
    
    if (file_size_bin(f, &size))
    {
        fclose(f);
        return DATA_ERROR;
    }

    combsort_bin(f, size);


    fseek(f, 0L, SEEK_SET);

    for (size_t i = 0; i < size; i++)
    {
        struct student temp;
        get_student_by_pos(f, 0, &temp);

        printf("%s\n", temp.first_name);
        printf("%s\n", temp.second_name);

        printf("%d\n", temp.marks[0]);
        printf("%d\n", temp.marks[1]);
        printf("%d\n", temp.marks[2]);
        printf("%d\n", temp.marks[3]);
    }

    fclose(f);

    return OK;
}

int delete_bad_bin(char *file_name)
{
    FILE *f;

    f = fopen(file_name, "r+b");

    if (f == NULL)
        return FILE_NAME_ERROR;

    size_t size = 0;

    if (file_size_bin(f, &size))
    {
        fclose(f);
        return DATA_ERROR;
    }
        
    double sum = 0;
    size_t n = 0;

    for (int i = 0; i < size; i++)
    {
        struct student temp;
        
        get_student_by_pos(f, i, &temp);
        
        sum += temp.marks[0] + temp.marks[1] + temp.marks[2] + temp.marks[3];

        n += 4;
    }

    double avg = sum / n;

    int k = 0;
    double local_avg = 0;

    for (int i = 0; i < size; i++)
    {
        struct student temp;
        
        get_student_by_pos(f, i, &temp);

        local_avg = (temp.marks[0] + temp.marks[1] + temp.marks[2] + temp.marks[3]) / 4.0;

        if (local_avg < avg)
            continue;

        put_student_by_pos(f, k++, temp);
    }

    fflush(f);

    ftruncate(fileno(f), k * sizeof(struct student));

    fclose(f);

    return OK;
}
