#ifndef _IO_FUNC_H
#define _IO_FUNC_H

#define MAX_STR_LEN 257
#define MAX_WORD_COUNT 126
#define MAX_WORD_LEN 17

int input_words_array(char (*words)[MAX_WORD_LEN], int *words_count);

void print_words_array(char const (*words)[MAX_WORD_LEN], int word_count);

#endif