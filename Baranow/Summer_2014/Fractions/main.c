#include <stdio.h>
#include <stdlib.h>

typedef struct {
	unsigned int a, b;
	int c;
} t_pfrac;

int fnc_nod(int a, int b)
{
    a = abs(a);
    b = abs(b);
    while ((a != 0) && (b != 0))
    {
        if (a > b)
            a = a % b;
        else
            b = b % a;
    }
    return a + b;
}

int fnc_nok(int a, int b)
{
    return (a * b / fnc_nod(a, b));
}

/*
    "Нормализует" дробь,
    превращает неправильную дробь в правильную.
*/
t_pfrac pfrac_normalize (t_pfrac f1)
{
    if (f1.b < abs(f1.c)) return f1;
    while (f1.b >= abs(f1.c))
    {
        f1.a += 1;
        f1.b -= abs(f1.c);
    }
	pfrac_shrink(&f1);
    return f1;
}

/*
    "Денормализует" дробь,
    переводит всю целую часть в числитель (превращает дробь в неправильную).
    Пример : 1[1/2] >> 3/2.
*/
t_pfrac pfrac_denormalize (t_pfrac f1)
{
    if (f1.a == 0) return f1;
    while (f1.a != 0)
    {
        f1.a -= 1;
        f1.b += abs(f1.c);
    }
    return f1;
}

/*
    Работаем по ссылке.
    Сокращает дробь до минимально возможной.
*/
void pfrac_shrink(t_pfrac *f1)
{
    if (f1->c == 0) return;
	int nod = fnc_nod(f1->b, abs(f1->c));
	if (nod != 1)
	{
		f1->b = f1->b / nod;
		f1->c = f1->c / nod;
	}
}

/*
    "Переворачивает" дробь.
    Используется при делении дробей.
*/
t_pfrac pfrac_reverse(t_pfrac f1)
{
    t_pfrac A, B;
    int sign;

    if (f1.c == 0)
    {
        return f1;
    }
    A = pfrac_denormalize(f1);
    sign = abs(A.c) / A.c;

    B.a = 0;
    B.b = abs(A.c);
    if (A.b == 0) A.b = 1;
    B.c = A.b * sign;

    return pfrac_normalize(B);
}

/*
    Работаем по ссылке.
    Приводит две дроби к одинаковому знаменателю.
*/
void pfrac_toEqual (t_pfrac *f1, t_pfrac *f2)
{
    int nok, sign1, sign2;
    if ((f1->c == 0) || (f2->c == 0)) return;

    *f1 = pfrac_denormalize(*f1);
    *f2 = pfrac_denormalize(*f2);

    sign1 = abs(f1->c) / f1->c;
    sign2 = abs(f2->c) / f2->c;
    nok = fnc_nok(abs(f1->c), abs(f2->c));

    f1->b = f1->b * nok / abs(f1->c);
    f1->c = nok * sign1;
    f2->b = f2->b * nok / abs(f2->c);
    f2->c = nok * sign2;
}

/*
    Создание новой дроби.
*/
t_pfrac pfrac_new (unsigned int a, unsigned int b, int c)
{
    t_pfrac A;
    A.a = abs(a);
    A.b = abs(b);
	A.c = (!((A.b == 0) && (A.c == 0)))? c : 0;
    return A;
}

void pfrac_print (t_pfrac f)
{
    printf("[%i %i/%i]", f.a, f.b, f.c);
}

int pfrac_correct (t_pfrac f)
{
    return (f.c == 0)? 0: 1;
}

/*
    Сложение, вычитание, умножение и деление двух дробей.
*/
t_pfrac	pfrac_add (t_pfrac f1, t_pfrac f2)
{
    int sign0, sign1, sign2;
	t_pfrac C, D;

	f1 = pfrac_denormalize(f1);
	f2 = pfrac_denormalize(f2);
	pfrac_toEqual(&f1, &f2);

	if (pfrac_cmp(f1, f2) == 0)
    {
        f1.b *= 2;
        return pfrac_normalize(f1);
    }
    sign1 = abs(f1.c) / f1.c;
    sign2 = abs(f2.c) / f2.c;

    if ((sign1 + sign2) == 2) sign0 = 1;
    if ((sign1 + sign2) == -2) sign0 = -1;
    if ((sign1 + sign2) == 0)
    {
        // смотрим по модулю что больше и тот же знак будет в ответе
        C = f1; C.c = abs(C.c);
        D = f2; D.c = abs(D.c);

        sign0 = 1;
        if (pfrac_cmp(C, D) == 1) sign0 = abs(f1.c) / f1.c;
        if (pfrac_cmp(C, D) == -1) sign0 = abs(f2.c) / f2.c;
    }
    C.a = 0;
    C.b = abs(f1.b * sign1 + f2.b * sign2);
    C.c = abs(f1.c) * sign0;

    return pfrac_normalize(C);
}

t_pfrac	pfrac_sub (t_pfrac f1, t_pfrac f2)
{
    f2.c = -f2.c;
    return pfrac_add(f1, f2);
}

t_pfrac	pfrac_mul (t_pfrac f1, t_pfrac f2)
{
    t_pfrac res, A, B;
    int sign;

    A = pfrac_denormalize(f1);
    B = pfrac_denormalize(f2);

    sign = ((A.c * B.c) < 0)? -1: 1;
    res.a = 0;
    res.b = A.b * B.b;
    res.c = abs(A.c) * abs(B.c) * sign;

    return pfrac_normalize(res);
}

t_pfrac	pfrac_div (t_pfrac f1, t_pfrac f2)
{
    t_pfrac A;
    A = pfrac_reverse(f2);
    return pfrac_mul(f1, A);
}

/*
    Сравнение двух дробей.
*/
int pfrac_cmp (t_pfrac f1, t_pfrac f2)
{
    int sign1, sign2;
    t_pfrac A, B;

    if ((f1.c == 0) || (f2.c == 0)) return 0;

    sign1 = abs(f1.c) / f1.c;
    sign2 = abs(f2.c) / f2.c;

    if (sign1 > sign2) return 1;
    if (sign1 < sign2) return -1;

    A = pfrac_denormalize(f1);
    B = pfrac_denormalize(f2);

    if (f1.c != f2.c)
    {
        pfrac_toEqual(&A, &B);
    }
    if (A.b > B.b) return 1;
    if (A.b == B.b) return 0;
    if (A.b < B.b) return -1;
}

int main()
{
    t_pfrac A, B, C;
    int a, b, c;

    scanf("%i %i %i", &a, &b, &c);
    A = pfrac_new(a, b, c);
    scanf("%i %i %i", &a, &b, &c);
    B = pfrac_new(a, b, c);
    C = pfrac_add(A, B);
    pfrac_print(C);

    printf("\n\n\n");

    scanf("%i %i %i", &a, &b, &c);
    A = pfrac_new(a, b, c);
    scanf("%i %i %i", &a, &b, &c);
    B = pfrac_new(a, b, c);
    C = pfrac_sub(A, B);
    pfrac_print(C);

    printf("\n\n\n");

    scanf("%i %i %i", &a, &b, &c);
    A = pfrac_new(a, b, c);
    scanf("%i %i %i", &a, &b, &c);
    B = pfrac_new(a, b, c);
    C = pfrac_mul(A, B);
    pfrac_print(C);

    printf("\n\n\n");

    scanf("%i %i %i", &a, &b, &c);
    A = pfrac_new(a, b, c);
    scanf("%i %i %i", &a, &b, &c);
    B = pfrac_new(a, b, c);
    C = pfrac_div(A, B);
    pfrac_print(C);

    return 0;
}
