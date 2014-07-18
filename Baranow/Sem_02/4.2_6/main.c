#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TRUE 1
#define FALSE 0

int exclude(char c)
{
    if ((c == 'a') || (c == 'e') || (c == 'h') || (c == 'i') || (c == 'o') || (c == 'u') || (c == 'w') || (c == 'y')) return TRUE; else return FALSE;
}

char changeTo(char c)
{
    if ((c == 'b') || (c == 'f') || (c == 'p') || (c == 'v')) return 1;
    if ((c == 'c') || (c == 'g') || (c == 'j') || (c == 'k') || (c == 'q') || (c == 's') || (c == 'x') || (c == 'z')) return 2;
    if ((c == 'd') || (c == 't')) return 3;
    if (c == 'l') return 4;
    if ((c == 'm') || (c == 'n')) return 5;
    if (c == 'r') return 6;
    return 0;
}

int soundex (const char *str, char B[4])
{
    char *A, c;
    int i, j, k, counter;

    A = (char*) malloc (sizeof(char));
    i = -1;
    for (k = 0; k < strlen(str); ++k)
    {
        c = tolower(str[k]);
        if (exclude(c) == TRUE) continue;
        if ((j = changeTo(c)) > 0)
        {
            ++i;
            *(A+i) = j;
            A = realloc(A, sizeof(char)*(i+2));
        }
    }

    for (k = 0; k < 4; ++k) B[k] = '0';
    B[0] = str[0];

    for (k = 0, c = 0, counter = 1, j = 0; j <= i; ++j)
    {
        if (A[j] != c)
        {
            ++k;
            c = A[j];
            B[k] = A[j] + 48;
            ++counter;
        }
        if (counter >= 4) break;
    }
    free(A);
    return 0;
}

int main()
{
    int i;
    char *str, *B;

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

    B = malloc(sizeof(char)*5);
    B[4] = '\0';

    soundex(str, B);
    printf("1. %s \n2. %s", str, B);
    return 0;
}
