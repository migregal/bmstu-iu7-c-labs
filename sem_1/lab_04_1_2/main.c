#include <stdio.h>
#include <string.h>

#include "io_func.h"
#include "matrix_sort.h"

#define OK 0
#define INPUT_ERROR 1
#define LOGIC_ERROR 2
#define OUTPUT_ERROR 3

int main(void)
{
    char words[MAX_WORD_COUNT][MAX_WORD_LEN];
    int words_count;

    if (input_words_array((char (*)[MAX_WORD_LEN]) words, &words_count))
        return INPUT_ERROR;
    
    sort_words_array((char (*)[MAX_WORD_LEN]) words, words_count);

    print_words_array((char const (*)[MAX_WORD_LEN]) words, words_count);

    return OK;
}