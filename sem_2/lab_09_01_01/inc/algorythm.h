#ifndef __MY_ALGORYTHM_H__
#define __MY_ALGORYTHM_H__

#include "film.h"

#define SORT_FIELD_TITLE "title"
#define SORT_FIELD_NAME "name"
#define SORT_FIELD_YEAR "year"

int read_file(films_vec *films, char *file_name, int flag);

int bin_search(films_vec *films, int flag, char *value, film **res);

int run_command(films_vec *films, char *f_name, int sort_f, int search_f, char *search_v, film **res);

#endif
