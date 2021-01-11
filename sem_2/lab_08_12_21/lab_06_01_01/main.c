#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "film.h"

#define SORT_FIELD_TITLE "title"
#define SORT_FIELD_NAME "name"
#define SORT_FIELD_YEAR "year"

#define OK 0
#define COMMAND_FORMAT_ERROR 100
#define FILE_ENDED 101
#define ARRAY_SORTED 102
#define FILM_NOT_FOUND 103
#define FILM_FOUND 104

int read_string(FILE *src, int max_len, char *dest)
{
    char *str = dest, ch;

    while (fscanf(src, "%c", &ch) == 1 && ch != '\n' && str < dest + max_len)
        *str++ = ch;

    if (feof(src))
        return FILE_ENDED;

    if ((str == dest) || (ch != '\n' && str == dest + max_len))
        return DATA_ERROR;

    *str = '\0';

    return OK;
}

int read_file(films_arr *films, char *file_name, int flag)
{
    FILE *fin;

    fin = fopen(file_name, "r");

    if (fin == NULL)
        return FILE_NAME_ERROR;

    film temp;

    for (int c, i = 0; ; i++)
    {
        c = read_string(fin, MAX_TITLE_LENGTH + 1, temp.title);

        if (c == FILE_ENDED)
            break;

        if (c != OK)
        {
            fclose(fin);
            return DATA_ERROR;
        }

        c = read_string(fin, MAX_NAME_LENGTH + 1, temp.name);

        if (c != OK || fscanf(fin, "%d", &temp.year) != 1 || temp.year <= 0)
        {
            if (fclose(fin))
                exit(EXIT_FAILURE);

            return DATA_ERROR;
        }

        if (append(films, &temp))
        {
            if (fclose(fin))
                exit(EXIT_FAILURE);

            return ARRAY_SIZE_OVERFLOW_ERR;
        }

        fgetc(fin);
    }

    if (fclose(fin))
        exit(EXIT_FAILURE);

    if (flag == TITLE_SORT_FLAG)
        qsort(films->arr, len(films), sizeof(film), &compare_title);
    else if (flag == NAME_SORT_FLAG)
        qsort(films->arr, len(films), sizeof(film), &compare_name);
    else if (flag == YEAR_SORT_FLAG)
        qsort(films->arr, len(films), sizeof(film), &compare_year);
    else
        return WRONG_FLAG_ERROR;

    return OK;
}

int bin_search(films_arr *films, int flag, char *value, film **res)
{
    film temp;

    if (flag == TITLE_SORT_FLAG)
    {
        strcpy(temp.title, value);
        *res = (film *)bsearch(&temp, films->arr, len(films), sizeof(film), &compare_title);
    }
    else if (flag == NAME_SORT_FLAG)
    {
        strcpy(temp.name, value);
        *res = (film *)bsearch(&temp, films->arr, len(films), sizeof(film), &compare_name);
    }
    else if (flag == YEAR_SORT_FLAG)
    {
        char *end;
        temp.year = (int)strtol(value, &end, 10);

        if ((size_t)(end - value) != strlen(value))
            return COMMAND_FORMAT_ERROR;

        *res = (film *)bsearch(&temp, films->arr, len(films), sizeof(film), &compare_year);
    }

    if (*res == NULL)
        return FILM_NOT_FOUND;

    return FILM_FOUND;
}

int parse_args(int argc, char **argv, int *sort_flag, int *search_flag)
{
    if (argc < 3 || argc > 4)
        return COMMAND_FORMAT_ERROR;

    if (strcmp(argv[2], SORT_FIELD_TITLE) == 0)
        *sort_flag = TITLE_SORT_FLAG;
    else if (strcmp(argv[2], SORT_FIELD_NAME) == 0)
        *sort_flag = NAME_SORT_FLAG;
    else if (strcmp(argv[2], SORT_FIELD_YEAR) == 0)
        *sort_flag = YEAR_SORT_FLAG;
    else
        return WRONG_FLAG_ERROR;

    if (argc == 3)
        *search_flag = NO_SEARCH_FLAG;

    return OK;
}

int run_command(films_arr *films, char *f_name, int sort_f, int search_f, char *search_v, film **res)
{
    int err = read_file(films, f_name, sort_f);

    if (err)
        return INPUT_FILE_ERROR;

    if (len(films) == 0)
        return ARRAY_IS_EMPTY_ERR;

    if (search_f == NO_SEARCH_FLAG)
        return ARRAY_SORTED;

    return bin_search(films, sort_f, search_v, res);
}

int main(int argc, char **argv)
{
    int search_flag = SEARCH_FLAG;
    int sort_flag = 0;

    if (parse_args(argc, argv, &sort_flag, &search_flag) != OK)
        return COMMAND_FORMAT_ERROR;

    films_arr films;
    clear(&films);

    film *movie;

    int res = run_command(&films, argv[1], sort_flag, search_flag, argv[3], &movie);

    if (res == FILM_FOUND)
    {
        printf("%s\n%s\n%d\n", movie->title, movie->name, movie->year);
        return OK;
    }

    if (res == FILM_NOT_FOUND)
    {
        printf("Not found\n");
        return OK;
    }

    if (res != ARRAY_SORTED)
        return res;

    film temp;
    for (size_t i = 0; i < len(&films); i++)
    {
        if (get(&films, i, &temp))
            return DATA_ERROR;

        printf("%s\n%s\n%d\n", temp.title, temp.name, temp.year);
    }

    return OK;
}
