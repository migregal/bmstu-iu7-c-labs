#include <stdio.h>

#define MIN_IN_HOURS 60
#define SEC_IN_HOURS 3600
#define SEC_IN_MINS 60

int main(void)
{
    int t;
    int h, m, s;

    printf("Input seconds:\n    ");
    scanf("%d", &t);

    h = t / SEC_IN_HOURS;
    m = (t % SEC_IN_HOURS) / MIN_IN_HOURS;
    s = (t % SEC_IN_HOURS) % SEC_IN_MINS;

    printf("It is:\n    %d h. %d min. %d sec.\n", h, m, s);

    return 0;
}
