#include <sys/types.h>
#include <unistd.h>

#include <stdio.h>

#include "film.h"
#include "io.h"

#define MIN(_x_, _y_) (_x_ > _y_ ? _y_ : _x_)

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

    if (!memcpy(temp->title, buf, sizeof(char) * MIN(str_len, STR_LEN)))
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
        return DATA_ERROR;
    }
    buf[str_len - 1] = '\0';

    if (!memcpy(temp->name, buf, sizeof(char) * MIN(str_len, STR_LEN)))
    {
        LOG_ERROR("Memory allocation error");
        free(buf);
        return MEM_ALLOC_ERR;
    }

    LOG_DEBUG("Name is %s", temp->name);

    LOG_DEBUG("Year reading");

    str_len = getline(&buf, &buf_size, fin);

    if (2 > str_len)
    {
        LOG_ERROR("Year reading error");
        free(buf);
        return DATA_ERROR;
    }

    char sym = 0;
    if (2 != sscanf(buf, "%d%c", &(temp->year), &sym) || temp->year <= 0 || sym != '\n')
    {
        LOG_ERROR("Incorrect year");
        free(buf);
        return DATA_ERROR;
    }

    LOG_DEBUG("Year is %d", temp->year);

    free(buf);

    return OK;
}

int read_file(node_t **head, char *file_name)
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

    LOG_DEBUG("Reading from file");

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

        node_t *node = NULL;
        if (create_node(&node, &temp, sizeof(film)))
        {
            LOG_ERROR("Node allocating error");
            free_list(head);

            if (fclose(fin))
                exit(EXIT_FAILURE);

            return DATA_ERROR;
        }

        sorted_insert(head, node, compare_films);
    }

    return fclose(fin);
}

int write_file(node_t **head, char *file_name)
{
    FILE *fout;

    LOG_DEBUG("Opening file");

    fout = fopen(file_name, "w");

    if (!fout)
    {
        LOG_ERROR("File opening error");
        return FILE_NAME_ERROR;
    }

    LOG_DEBUG("Writing to file");

    void *temp = NULL;

    while ((temp = pop_front(head)))
    {
        film *f = (film *)temp;

        fprintf(fout, "%s\n%s\n%d\n", f->name, f->title, f->year);

        free(temp);
    }

    LOG_DEBUG("Written");

    return fclose(fout);
}
