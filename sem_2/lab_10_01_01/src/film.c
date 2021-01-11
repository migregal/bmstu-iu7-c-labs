#include "film.h"

#define MIN(_x_, _y_) (_x_ > _y_ ? _y_ : _x_)

void free_film(void *temp)
{
    free(((film *)temp)->name);
    free(((film *)temp)->title);
}

int init_film(film *temp, const char *title, const char *name)
{
    if (temp->title || temp->name)
        return MEM_ACCESS_ERR;

    if (!title || !memcpy(temp->title, title, sizeof(char) * MIN(strlen(title), STR_LEN)))
        return MEM_ALLOC_ERR;

    temp->title[MIN(strlen(title), STR_LEN)] = '\0';

    if (!name || !memcpy(temp->name, name, sizeof(char) * MIN(strlen(name), STR_LEN)))
        return MEM_ALLOC_ERR;

    return OK;
}

int compare_title(const void *first, const void *second)
{
    return strcmp(((film *)first)->title, ((film *)second)->title);
}

int compare_name(const void *first, const void *second)
{
    return strcmp(((film *)first)->name, ((film *)second)->name);
}

int compare_year(const void *first, const void *second)
{
    if (((film *)first)->year > ((film *)second)->year)
        return 1;

    if (((film *)first)->year < ((film *)second)->year)
        return -1;

    return 0;
}

int compare_films(const void *first, const void *second)
{
    if (compare_name(first, second))
        return compare_name(first, second);

    if (compare_title(first, second))
        return compare_title(first, second);

    return compare_year(first, second);
}
