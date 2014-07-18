#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main()
{
    int a, b, n, sum, m, i;
    scanf("%i %i", &a, &n);
    m = sizeof(a)*8 / n;

    a = INT_MAX-1;

    for (i = sizeof(a)*8-1, sum = 0; i >= 0; i--) {
        printf("%i", ((a >> i) & 1));
    }
    printf("\n");
    for (i = sizeof(a)*8-1, sum = 0; i >= 0; i--)
    {
        b = ((a >> i) & 1);
        sum += b;
        if ((i % n == 0) || (i == 0))
        {
            printf("%i ", sum);
            sum = 0;
        }
    }
    return 0;
}
