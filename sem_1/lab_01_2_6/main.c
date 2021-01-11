#include <stdio.h>
#include <math.h>

#define OK 0
#define IN_ERR 1
#define LOGIC_ERR 2

#define TRUE 1
#define FALSE 0

#define IN_TRIANGLE 0
#define ON_THE_SIDE 1
#define OUTSIDE_TRIANGLE 2

#define EPS 0.000001
/**
 * @brief sect_len 
 * @param x1 - x coordinate of 1 point
 * @param y1 - x coordinate of 1 point
 * @param x2 - x coordinate of 2 point
 * @param y2 - y coordinate of 2 point
 * @return calculates length of the section
 */
float sect_len(float x1, float y1, float x2, float y2)
{
    return sqrtf((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}
/**
 * @brief vect
 * @param xa - x coordinate of 1 point
 * @param ya - x coordinate of 1 point
 * @param xb - x coordinate of 2 point
 * @param yb - x coordinate of 2 point
 * @param x0 - x coordinate of 3 point
 * @param y0 - x coordinate of 3 point
 * @return vector product of 2 vectors by it's vertices coordinates
 */
float vect(float xa, float ya, float xb, float yb, float x0, float y0)
{
    return (xa - x0) * (yb - ya) - (xb - xa) * (ya - y0);
}

/**
 * @brief is_triangle
 * @param xa - x coordinate of 1 point
 * @param ya - y coordinate of 1 point
 * @param xb - x coordinate of 2 point
 * @param yb - y coordinate of 2 point
 * @param xc - x coordinate of 3 point
 * @param yc - y coordinate of 3 point
 * @return is 3 point is a triangle vertices
 */
int is_triangle(float xa, float ya, float xb, float yb, float xc, float yc)
{
    float ab, bc, ac;

    ab = sect_len(xa, ya, xb, yb);
    bc = sect_len(xb, yb, xc, yc);
    ac = sect_len(xa, ya, xc, yc);

    if (ab < bc + ac && bc < ab + ac && ac < ab + bc)
        return TRUE;

    return FALSE;
}

/**
 * @brief point_pos
 * @param xa - x coordinate of triangle 1 vertice
 * @param ya - y coordinate of triangle 1 vertice
 * @param xb - x coordinate of triangle 2 vertice
 * @param yb - y coordinate of triangle 2 vertice
 * @param xc - x coordinate of triangle 3 vertice
 * @param yc - y coordinate of triangle 3 vertice
 * @param x0 - x coordinate of point
 * @param y0 - y coordinate of point
 * @return position of a point
 */
int point_pos(float xa, float ya, float xb, float yb,
float xc, float yc, float x0, float y0)
{
    float ins_ab, ins_bc, ins_ac;

    ins_ab = vect(xa, ya, xb, yb, x0, y0);
    ins_bc = vect(xb, yb, xc, yc, x0, y0);
    ins_ac = vect(xc, yc, xa, ya, x0, y0);

    if ((ins_ab > 0 && ins_ac > 0 && ins_bc > 0) ||
        (ins_ab < 0 && ins_ac < 0 && ins_bc < 0))
        return IN_TRIANGLE;

    if (fabs(ins_ab) < EPS && (ins_bc * ins_ac >= 0))
        return ON_THE_SIDE;

    if (fabs(ins_ac) < EPS && (ins_bc * ins_ab >= 0))
        return ON_THE_SIDE;

    if (fabs(ins_bc) < EPS && (ins_ab * ins_ac >= 0))
        return ON_THE_SIDE;

    return OUTSIDE_TRIANGLE;
}

int main(void)
{
    float x0, y0, xa, ya, xb, yb, xc, yc;

    printf("Input triangle's vertices and a point:\n    ");

    if (scanf("%f %f %f %f %f %f %f %f",
    &xa, &ya, &xb, &yb, &xc, &yc, &x0, &y0) != 8)
    {
        printf("Input error\n");

        return IN_ERR;
    }

    if (!is_triangle(xa, ya, xb, yb, xc, yc))
    {
        printf("There is not triangle\n");
        return LOGIC_ERR;
    }

    printf("%d\n", point_pos(xa, ya, xb, yb, xc, yc, x0, y0));
    return OK;
}
