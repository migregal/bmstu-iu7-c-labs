#include <stdio.h>

int main(void)
{
    float r1, r2, r3;

    printf("Input resistances in Om's:\n    ");

    scanf("%f %f %f", &r1, &r2, &r3);

    float r0;

    r0 = (r1 * r2 * r3) / (r1 * r2 + r2 * r3 + r3 * r1);

    printf("Total resistance in parallel is:\n    %.5f\n", r0);

    return 0;
}
