#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../inc/common.h"
#include "../inc/film.h"
#include "../inc/algorythm.h"

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

int main(int argc, char **argv)
{
    int search_flag = SEARCH_FLAG;
    int sort_flag = 0;

    LOG_DEBUG("Parsing args");

    int err = OK;

    if (OK != (err = parse_args(argc, argv, &sort_flag, &search_flag)))
    {
        LOG_ERROR("Wrong args [%d]", err);
        return COMMAND_FORMAT_ERROR;
    }

    LOG_DEBUG("Memory allocation");

    films_vec films = {.arr = NULL, .len = 0, .cap = 0};

    film *movie;

    LOG_DEBUG("Running command");

    switch ((err = run_command(&films, argv[1], sort_flag, search_flag, argv[3], &movie)))
    {
    case FILM_FOUND:
        LOG_DEBUG("Film found");
        printf("%s\n%s\n%d\n", movie->title, movie->name, movie->year);

        clear(&films);

        return OK;
    case FILM_NOT_FOUND:
        LOG_DEBUG("Film not found");

        clear(&films);
        printf("Not found\n");
        return OK;
    case ARRAY_SORTED:
    {
        LOG_DEBUG("Array sorted");

        film temp;
        for (size_t i = 0; i < len(&films); i++)
        {
            if (OK != (err = get(&films, i, &temp)))
            {
                clear(&films);
                return DATA_ERROR;
            }

            printf("%s\n%s\n%d\n", temp.title, temp.name, temp.year);
        }

        clear(&films);
        return OK;
    }
    default:
        break;
    }

    LOG_ERROR("Error occured [%d]", err);

    clear(&films);
    return err;
}
