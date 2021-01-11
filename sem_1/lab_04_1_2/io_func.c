#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "io_func.h"

#define OK 0
#define INPUT_ERROR 1

#define TRUE 1
#define FALSE 0

void get_word(char *word, const char *const l, const char *const r)
{
    const char *i = l;
    while ((i <= r) && (i - l < MAX_WORD_LEN) && (*word++ = *i++));
    *word = '\0';
}

int is_word_uniq(const char *word, char (*words)[MAX_WORD_LEN], int count)
{
    for (const char *row = words[0];
        row < (const char*) words + count * MAX_WORD_LEN;
        row += MAX_WORD_LEN)
        if (strcmp(word, row) == 0)
            return FALSE;

    return TRUE;
}

int split_line(const char *line, char (*words_array)[MAX_WORD_LEN], int *word_count)
{
    char separators[] = ",;:-.!? \n\0";

    char word[MAX_WORD_LEN];
    *word_count = 0;

    for (const char *l = line, *r = line; *r; r++)
    {
        if ((r == line || strchr(separators, *(r - 1))) && !strchr(separators, *r))
            l = r;
        
        if (!strchr(separators, *r) && strchr(separators, *(r + 1)))
        {
            if (r - l + 1 > MAX_WORD_LEN)
                return INPUT_ERROR;
            
            get_word(word, l, r);

            if (is_word_uniq(word, words_array, *word_count))
                strcpy(words_array[(*word_count)++], word);
        }
    }
    
    return *word_count ? OK : INPUT_ERROR;
}

int input_words_array(char (*words)[MAX_WORD_LEN], int *words_count)
{
    char line[MAX_STR_LEN];

    if (!fgets(line, MAX_STR_LEN, stdin) || line[strlen(line) - 1] != '\n')
        return INPUT_ERROR;

    if (split_line(line, words, words_count))
        return INPUT_ERROR;
    
    return OK;
}

void print_words_array(char const (*words)[MAX_WORD_LEN], int word_count)
{
    printf("Result: ");
    for (const char *row = words[0];
        row < (const char*) words + word_count * MAX_WORD_LEN;
        row += MAX_WORD_LEN, printf(" "))
        printf("%s", row);

    printf("\n");
}