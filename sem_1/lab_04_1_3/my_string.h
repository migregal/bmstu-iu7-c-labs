#ifndef _MY_STRING_H_
#define _MY_STRING_H_

#define MAX_STR_LEN 257
#define MAX_WORD_COUNT 126
#define MAX_WORD_LEN 17

int split_line(const char *line, char (*words_array)[MAX_WORD_LEN], int *word_count);

int input_words_array(char (*words)[MAX_WORD_LEN], int *words_count);

void rmv_repeated_letters(char *const word);

int print_words_except_last(char const (*words)[MAX_WORD_LEN], int word_count);

#endif
