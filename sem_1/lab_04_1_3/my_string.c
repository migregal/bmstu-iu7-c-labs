#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "my_string.h"

#define OK 0
#define INPUT_ERROR 1
#define OUTPUT_ERROR 1

int split_line(const char *line, char (*words_array)[MAX_WORD_LEN], int *const word_count)
{
    char separators[] = ",;:-.!? \n\0";

    *word_count = 0;

    char *istr = strtok((char *) line, separators);
    while (istr != NULL)
    {
        strcpy(words_array[(*word_count)++], istr);
        istr = strtok(NULL, separators);
    }
    
    return *word_count ? OK : INPUT_ERROR;
}

int input_words_array(char (*words)[MAX_WORD_LEN], int *const words_count)
{
    char line[MAX_STR_LEN];

    if (!fgets(line, MAX_STR_LEN, stdin) || line[strlen(line) - 1] != '\n')
        return INPUT_ERROR;

    if (split_line(line, words, words_count))
        return INPUT_ERROR;
    
    if (*words_count <= 1)
        return INPUT_ERROR;

    return OK;
}

void rmv_repeated_letters(char *const word)
{   
    char *l = (char *) word, *r;
    while (*l && (r = l))
    {
        if (strchr(word, (int) *l) == l && l++)
            continue;

        while (*r && (*r = *(r + 1)) && (r++));
    }
}

int print_words_except_last(char const (*words)[MAX_WORD_LEN], const int word_count)
{
    for (int i = 0; i < word_count; i++)
    {
        if (strcmp(words[word_count - 1], words[i]) != 0)
            break;
        
        if (i == word_count - 1)
            return OUTPUT_ERROR;
    }

    printf("Result:");
 
    int printed_words = word_count;
    for (int i = word_count - 1; i >= 0; i--)
    {
        if (strcmp(words[word_count - 1], words[i]) != 0)
        {
            printf(" %s", words[i]);
            --printed_words;
        }
    }
        
    printf("\n");
    
    return OK;
}