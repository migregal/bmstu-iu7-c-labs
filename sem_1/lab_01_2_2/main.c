#include <stdio.h>
#include <math.h>

int main(void)
{
    float x1, y1, x2, y2, x3, y3;

    printf("Input triangles vertices:\n    ");

    scanf("%f %f %f %f %f %f", &x1, &y1, &x2, &y2, &x3, &y3);

    float len1, len2, len3;

    len1 = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
    len2 = sqrt((x1 - x3) * (x1 - x3) + (y1 - y3) * (y1 - y3));
    len3 = sqrt((x3 - x2) * (x3 - x2) + (y3 - y2) * (y3 - y2));

    printf("Triangles perimeter is: %.5f\n", len1 + len2 + len3);

    return 0;
}
