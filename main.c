// #include <stdio.h>
// #include <stdlib.h>
// #include <time.h>
// #include <assert.h>
// #include <stdint.h>
// #include <string.h>
// #include <math.h>
#include "helper.h"

// typedef struct {
//     int a;
//     int b;
//     int c;
// } form;

typedef struct
{
    int first;
    int second;
} Pair;

Pair extended_gcd(int a, int b)
{
    if (b == 0)
    {
        Pair p = {1, 1};
        return p;
    }
    Pair ans = extended_gcd(b, a % b);
    int x = ans.second, y = ans.first - (a / b) * ans.second;
    ans.first = x;
    ans.second = y;
    return ans;
}

int solve_congruence(int a, Pair *x, int b, int m)
{
    Pair res; // res.first = d, res.second = e
    res = extended_gcd(a, m);

    int g = gcd(a, m);
    if (b % g)
        return 1;

    int q = b / g;
    (*x).first = (q * res.first) % m;
    (*x).second = m / g;

    return 0;
}

int composed(form *a_form, form *b_form, form *c_form)
{
    int g = (a_form->b + b_form->b) / 2;       // 1
    int h = (b_form->b - a_form->b) / 2;       // 0
    int w = gcd(a_form->a, gcd(b_form->a, g)); // gcd(1, 2, 1) = 1

    int j = w;               // 1
    int r = 0;               // 0
    int s = (a_form->a / w); // 1
    int t = (b_form->a / w); // 2
    int u = (g / w);         // 1

    // check
    int num = b_form->c;
    num -= (((h * u) + (a_form->c * s)) / t);
    if (num)
        return 1;

    int tu = t * u; // 2
    int st = s * t; // 2
    Pair k_temp;

    if (solve_congruence(tu, &k_temp, h * u + s * a_form->c, st)) // 2, k, 6, 2 --->>> k.first=1 and k.second=1
        return 1;

    Pair n_temp;
    if (solve_congruence(t * k_temp.second, &n_temp, h - t * k_temp.first, s)) // 2, n, -2, 1 --->>> n.first=0 and n.second=1
        return 1;

    int temp;
    printf("\nChoose any value of n': "); // preferably 0
    scanf("%d", &temp);

    int n = n_temp.first + n_temp.second * temp; // if n' = 0 then n = 0 + 0 = 0

    int k = k_temp.first + k_temp.second * n; // k = 1 + 1 * 0 = 1
    int l = (k * t - h) / s;
    int m = (t * u * k - h * u - (a_form->c) * s) / (s * t);

    // printf("Values of k, l and m are:   %d  %d  %d", k, l, m);

    c_form->a = s * t - r * u;
    c_form->b = (j * u + m * r) - (k * t + l * s);
    c_form->c = k * l - j * m;

    return 0;
}

int normalized(form *c_form)
{
    int a = c_form->a; // 2
    int b = c_form->b; // -3
    int c = c_form->c; // 4

    if (b > ((-1) * a) && b <= a)
        return 0;

    if (a < 1)
        return 1;

    double r_ = floor((a - b) / (2 * a)); // 1
    if (r_ < 0)
        r_ -= 1;
    int r = (int)r_;

    c_form->b = b + 2 * r * a;
    c_form->c = (a * r * r) + (b * r) + c;

    return 0;
}

int reduced(form *c_form)
{
    normalized(c_form);

    int a = c_form->a; // 2
    int b = c_form->b; // -3
    int c = c_form->c; // 4

    if ((a == c && b >= 0) || a < c)
        return 0;

    double s_ = floor((c + b) / (2 * c)); // 0
    int s = (int)s_;

    c_form->a = c;
    c_form->b = ((-1) * b) + 2 * s * c;
    c_form->c = (c * s * s) - (b * s) + a;

    return 1;
}

int32_t main()
{
    int delta = -23;
    form p_form;
    p_form.a = 1;
    int k = delta % 2;
    if (k < 0)
        k += 2;
    p_form.b = k;

    printf("Using delta: %d", delta);
    p_form.c = (pow(k, 2) - delta) / 4;
    printf("\nPrincipal form: (%d, %d, %d)", p_form.a, p_form.b, p_form.c);

    form e_form = {2, 1, 3};
    printf("\nExample form: (%d, %d, %d)", e_form.a, e_form.b, e_form.c);

    // p_form.a = 2;
    // p_form.b = 1;
    // p_form.c = 3;

    // COMPOSITION
    form c_form;
    if (composed(&p_form, &e_form, &c_form))
    {
        printf("\nFAILED COMPOSITION");
        return 0;
    }
    else
        printf("Composed form: (%d, %d, %d)", c_form.a, c_form.b, c_form.c);

    // NORMALIZATION
    // c_form.a = 11;
    // c_form.b = 49;
    // c_form.c = 55;
    if (normalized(&c_form))
    {
        printf("\nFAILED NORMALIZATION");
        return 0;
    }
    else
        printf("\nNormalized form: (%d, %d, %d)", c_form.a, c_form.b, c_form.c);

    // REDUCTION
    // c_form.a = 11;
    // c_form.b = 49;
    // c_form.c = 55;
    while (reduced(&c_form))
        ;

    printf("\nReduced form: (%d, %d, %d)", c_form.a, c_form.b, c_form.c);

    return 0;
}
