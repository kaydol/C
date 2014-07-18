#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

typedef struct {
    int pos;
    int len;
} t_str;

char *str, *outstr;

int cmp(const void *a, const void *b)
{
    int L1 = ((t_str*)a)->len;
    int L2 = ((t_str*)b)->len;
    int P1 = ((t_str*)a)->pos;
    int P2 = ((t_str*)b)->pos;
    int i = -1;
    while ((i < L1 - 1) && (i < L2 - 1))
    {
        ++i;
        if (str[P1+i] > str[P2+i]) return 1;
        if (str[P1+i] < str[P2+i]) return -1;
    }
    if (L1 > L2) return 1;
    if (L1 < L2) return -1;
    if (L1 == L2) return 0;
}

int concat(char *S, int m, char *B)
{
    t_str *A;
    int i, j, k, h, size;

    if (strlen(S) % m == 0) size = strlen(S) / m;
    else size = strlen(S) / m + 1;

    A = (t_str*) malloc (sizeof(t_str) * size);

    for (k = 0, j = -1, i = 0; i < strlen(S); ++i)
    {
        ++k;
        if ((i % m == 0) || (i == 0))
        {
            ++j;
            A[j].pos = i;
            A[j].len = m;
            k = 0;
        }
    }
    if (strlen(S) % m != 0) A[j].len = strlen(S) % m;

    qsort(A, j+1, sizeof(t_str), cmp);

    for (h = -1, i = 0; i <= j; ++i)
        for (k = A[i].pos; k < A[i].pos + A[i].len; ++k)
        {
            ++h;
            B[h] = str[k];
        }

    free(A);
    return 0;
}

int main()
{
    int i, m;

    FILE *fin = fopen("input.txt", "r");
    if (fin == NULL) { printf("Can't find input file! --main!\n"); return -1; }

    i = -1;
    str = (char*) malloc(sizeof(char));
    while (!feof(fin))
    {
        ++i;
        str = realloc(str, sizeof(char) * (i+1));
        str[i] = fgetc(fin);
        if feof(fin) str[i] = '\0';
    }
    fclose(fin);
    printf("%s\n", str);

    outstr = (char*) malloc(sizeof(char) * (i+1));
    outstr[i] = '\0';

    scanf("%i",&m);
    concat(str, m, outstr);
    printf("%s", outstr);

    return 0;
}
