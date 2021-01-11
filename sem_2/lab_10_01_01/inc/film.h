#ifndef __FILM_H__
#define __FILM_H__

#include "common.h"

#define STR_LEN 256

typedef struct
{
    char title[STR_LEN];
    char name[STR_LEN];
    int year;
} film;

int init_film(film *, const char *, const char *);

void free_film(void *);

int compare_films(const void *, const void *);

#endif
