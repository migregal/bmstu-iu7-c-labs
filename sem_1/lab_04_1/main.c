#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 256

#include "my_string.h"

int main(void)
{
    printf("%zu\n", strcspn("LOST: 4-8-15-16-23-42", "1234567890"));
    printf("%zu\n", my_strcspn("LOST: 4-8-15-16-23-42", "1234567890"));

    printf("%zu\n", strcspn("0123456789", "abc"));
    printf("%zu\n", my_strcspn("0123456789", "abc"));

    return 0;
}