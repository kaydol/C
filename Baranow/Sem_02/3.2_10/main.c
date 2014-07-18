#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

double power(double t, int k)
{
    double res = 1;
    while (k)
    {
        if (k & 1) res *= t;
        t *= t;
        k >>= 1;
    }
    return res;
}

int main()
{
    int n, m, k;
    double d, Eps, first, last, next;

    printf("X[0] n Epsilon Limit\n");
    scanf("%lf %i %lf %i", &first, &n, &Eps, &m);

    k = 0;
    d = 10 * Eps;
    last = first;

    printf("%f >= %f\n", d, Eps);

    while ((k <= m) && (d >= Eps))
    {
        ++k;
        next = 1 / (double)n * ((n-1)*last + first / power(last, n-1));
        printf("%f\n", next);
        d = fabs(next - last);
        last = next;
    }
    printf("\n >> %f ", next);
    return 0;
}
