#include <stdio.h>

#define OK 0
#define IN_ERR 1
#define LOGIC_ERR -1
#define MAX_VALUE 92

/**
 * @brief fib - calculates the n-th number in a Fibonacci series
 * @param n - number (non-negative integer) number in a Fibonacci series
 * @return the n-th number in a Fibonacci series
 */
long long int fib(short n)
{
    long long int f0 = 0, f1 = 1;

    if (n < 0 || n > MAX_VALUE)
        return LOGIC_ERR;

    if (n <= 1)
        return n;

    for (int i = 2; i <= n; i++)
    {
        f1 += f0;
        f0 = f1 - f0;
    }

    return f1;
}

int main(void)
{
    int n;
    printf("Input non negative n:\n    ");

    if (scanf("%d", &n) != 1)
    {
        printf("Input error\n");
        return IN_ERR;
    }

    long long int res = fib(n);

    if (res == LOGIC_ERR)
    {
        printf("N isn't in correct interval\n");
        return LOGIC_ERR;
    }

    printf("%lld\n", res);
}
