#ifndef __FILM_H__
#define __FILM_H__

#include "common.h"

typedef struct
{
    char *title;
    char *name;
    int year;
} film;

typedef struct
{
    film *arr;
    size_t len, cap;
} films_vec;

size_t len(films_vec *);

int init_film(film *, const char *, const char *);

void free_film(film *);

int clear(films_vec *);

int get(films_vec *, size_t, film *);

int set(films_vec *, size_t, film *);

int append(films_vec *, film *);

int pop(films_vec *, film *);

int compare_title(const void *, const void *);

int compare_name(const void *, const void *);

int compare_year(const void *, const void *);

#endif
