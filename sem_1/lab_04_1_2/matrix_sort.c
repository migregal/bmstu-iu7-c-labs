#include <stdio.h>
#include <string.h>

#include "matrix_sort.h"

void my_strswap(char **str1_ptr, char **str2_ptr) 
{ 
    char *temp = *str1_ptr; 
    *str1_ptr = *str2_ptr; 
    *str2_ptr = temp; 
}   

void sort_words_array(char (*words)[MAX_WORD_LEN], int word_count)
{
    for (int i = 0; i < word_count; i++)
        for (int j = i; j > 0 && strcmp(words[j - 1], words[j]) > 0; j--)
            my_strswap((char **) words[j - 1], (char **) words[j]);
}