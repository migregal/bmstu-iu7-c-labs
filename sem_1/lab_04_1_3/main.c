#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "my_string.h"

#define OK 0
#define INPUT_ERROR 1
#define OUTPUT_ERROR 2

int main(void)
{
    char words[MAX_WORD_COUNT][MAX_WORD_LEN];
    int words_count;

    if (input_words_array((char (*)[MAX_WORD_LEN]) words, &words_count))
        return INPUT_ERROR;

    for (int i = 0; i < words_count; i++)
        rmv_repeated_letters(words[i]);

    if (print_words_except_last((char const (*)[MAX_WORD_LEN]) words, words_count))
        return OUTPUT_ERROR;

    return 0;
}