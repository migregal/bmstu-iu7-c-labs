#include <stdio.h>
#include <math.h>

#define OK 0
#define IN_ERR 1
#define LOGIC_ERR 2

#define EPS 0.000001
/**
 * @brief s_x - approximate value of f(x) function
 * @param x - argue to s(x)
 * @param eps - accuracy for s(x) finding
 * @return s(x) - approximate value of f(x)
 */
double s_x(double x, double eps)
{
    double res = 0;
    double t = x;
    long int n = 1;

    while (fabs(t) > eps)
    {
        res += t;

        t = t / (n + 1) / (n + 2) * n * n * x * x;

        n += 2;
    }

    return res;
}

int main(void)
{
    double x, eps;
    double fx, sx;
    double abs_err, rel_err;

    printf("Input x and eps:\n    ");

    if (scanf("%lf %lf", &x, &eps) != 2)
    {
        printf("Input error\n");

        return IN_ERR;
    }

    if (fabs(x) < 1 && eps > 0 && eps < 1)
    {
        sx = s_x(x, eps);
        fx = asin(x);

        abs_err = fabs(fx - sx);
        rel_err = (fabs(fx) < EPS) ? abs_err : fabs(abs_err / fx);

        printf("Result:\n    ");
        printf("%.6lf %.6lf %.6lf %.6lf\n", sx, fx, abs_err, rel_err);

        return OK;
    }
    else
    {
        printf("Wrong input datas\n");

        return LOGIC_ERR;
    }
}
