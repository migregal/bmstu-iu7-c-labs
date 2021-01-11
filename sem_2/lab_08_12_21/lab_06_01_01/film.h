#ifndef FILM_H
#define FILM_H

#define MAX_FILM_ARRAY_LENGTH 15

#define MAX_TITLE_LENGTH 25
#define MAX_NAME_LENGTH 25
#define MAX_YEAR_LENGTH 4

#define SEARCH_FLAG 1
#define NO_SEARCH_FLAG 2
#define TITLE_SORT_FLAG 3
#define NAME_SORT_FLAG 4
#define YEAR_SORT_FLAG 5
#define WRONG_FLAG_ERROR -1

#define FILE_NAME_ERROR 1
#define DATA_ERROR 2
#define INPUT_FILE_ERROR 3
#define FILE_READING_ERROR 4
#define ARRAY_IS_EMPTY_ERR 5
#define ARRAY_SIZE_OVERFLOW_ERR 6

typedef struct
{
    char title[MAX_TITLE_LENGTH + 1];
    char name[MAX_NAME_LENGTH + 1];
    int year;
} film;

typedef struct
{
    film arr[MAX_FILM_ARRAY_LENGTH];
    size_t len;
} films_arr;

size_t len(films_arr *);

int clear(films_arr *);

int get(films_arr *, size_t, film *);

int set(films_arr *, size_t, film *);

int append(films_arr *, film *);

int pop(films_arr *, film *);

int compare_title(const void *, const void *);

int compare_name(const void *, const void *);

int compare_year(const void *, const void *);

#endif
