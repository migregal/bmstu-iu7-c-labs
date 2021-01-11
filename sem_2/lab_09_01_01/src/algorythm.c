#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "../inc/common.h"
#include "../inc/film.h"

int read_film_info(FILE *fin, film *temp)
{
    char *buf = NULL;
    size_t buf_size = 0;

    LOG_DEBUG("Title reading");

    ssize_t str_len = getline(&buf, &buf_size, fin);

    if (2 > str_len)
    {
        LOG_ERROR("Title reading error");
        free(buf);
        return FILE_ENDED;
    }
    buf[str_len - 1] = '\0';
    temp->title = strdup(buf);

    if (!temp->title)
    {
        LOG_ERROR("Memory allcation error");
        free(buf);
        return MEM_ALLOC_ERR;
    }

    LOG_DEBUG("Title is %s", temp->title);

    LOG_DEBUG("Name reading");

    str_len = getline(&buf, &buf_size, fin);
    if (2 > str_len)
    {
        LOG_ERROR("Name reading error");
        free(buf);
        free(temp->title);
        return DATA_ERROR;
    }
    buf[str_len - 1] = '\0';
    temp->name = strdup(buf);

    if (!temp->name)
    {
        LOG_ERROR("Memory allocation error");
        free(buf);
        free(temp->title);
        return MEM_ALLOC_ERR;
    }

    LOG_DEBUG("Name is %s", temp->name);

    LOG_DEBUG("Year reading");

    str_len = getline(&buf, &buf_size, fin);

    if (2 > str_len)
    {
        LOG_ERROR("Year reading error");
        free(temp->name);
        free(temp->title);
        free(buf);
        return DATA_ERROR;
    }

    if (sscanf(buf, "%d", &(temp->year)) != 1 || temp->year <= 0)
    {
        LOG_ERROR("Incorrect year");
        free(temp->name);
        free(temp->title);
        free(buf);
        return DATA_ERROR;
    }

    LOG_DEBUG("Year is %d", temp->year);

    free(buf);

    return OK;
}

int read_file(films_vec *films, char *file_name, int flag)
{
    FILE *fin;

    LOG_DEBUG("Opening file");

    fin = fopen(file_name, "r");

    if (fin == NULL)
    {
        LOG_ERROR("File opening error");
        return FILE_NAME_ERROR;
    }

    film temp;

    LOG_DEBUG("Reading array from file");

    while (!feof(fin))
    {
        int err = read_film_info(fin, &temp);

        if (FILE_ENDED == err)
            break;

        if (err)
        {
            LOG_ERROR("Film reading error");

            if (fclose(fin))
                exit(EXIT_FAILURE);

            return DATA_ERROR;
        }

        LOG_DEBUG("Adding elem to vec");

        err = append(films, &temp);

        free_film(&temp);

        if (err)
        {
            LOG_ERROR("Elem adding error");

            if (fclose(fin))
                exit(EXIT_FAILURE);

            return ARRAY_SIZE_OVERFLOW_ERR;
        }
    }

    if (fclose(fin))
        exit(EXIT_FAILURE);

    LOG_DEBUG("Sorting vec");
    if (flag == TITLE_SORT_FLAG)
        qsort(films->arr, len(films), sizeof(film), &compare_title);
    else if (flag == NAME_SORT_FLAG)
        qsort(films->arr, len(films), sizeof(film), &compare_name);
    else if (flag == YEAR_SORT_FLAG)
        qsort(films->arr, len(films), sizeof(film), &compare_year);
    else
    {
        LOG_ERROR("Wrong sorting flag");
        return WRONG_FLAG_ERROR;
    }

    return OK;
}

int bin_search(films_vec *films, int flag, char *value, film **res)
{
    film temp = {.title = NULL, .name = NULL, .year = 0};

    if (flag == TITLE_SORT_FLAG)
    {
        if (init_film(&temp, value, ""))
            return MEM_ALLOC_ERR;

        *res = (film *)bsearch(&temp, films->arr, len(films), sizeof(film), &compare_title);

        goto result;
    }

    if (flag == NAME_SORT_FLAG)
    {
        if (init_film(&temp, "", value))
            return MEM_ALLOC_ERR;

        *res = (film *)bsearch(&temp, films->arr, len(films), sizeof(film), &compare_name);
        goto result;
    }

    if (flag == YEAR_SORT_FLAG)
    {
        char *end;
        temp.year = (int)strtol(value, &end, 10);

        if ((size_t)(end - value) != strlen(value))
            return COMMAND_FORMAT_ERROR;

        *res = (film *)bsearch(&temp, films->arr, len(films), sizeof(film), &compare_year);
    }

result:
    free_film(&temp);

    if (*res == NULL)
        return FILM_NOT_FOUND;

    return FILM_FOUND;
}

int run_command(films_vec *films, char *f_name, int sort_f, int search_f, char *search_v, film **res)
{
    LOG_DEBUG("Reading file");
    int err = OK;

    if ((err = read_file(films, f_name, sort_f)))
    {
        LOG_ERROR("File reading error");
        return err;
    }

    if (len(films) == 0)
    {
        LOG_ERROR("Empty array found");
        return ARRAY_IS_EMPTY_ERR;
    }

    if (search_f == NO_SEARCH_FLAG)
    {
        LOG_DEBUG("Search flag is empty");
        return ARRAY_SORTED;
    }

    LOG_DEBUG("Binary search");
    return bin_search(films, sort_f, search_v, res);
}
