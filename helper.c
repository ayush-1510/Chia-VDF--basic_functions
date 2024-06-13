#include "helper.h"

form *gen_forms(int delta, int num, int *ct)
{
    int temp;
    temp = (-1) * delta;
    temp /= 3;
    int e = sqrt(temp);
    int s = 1;

    form *forms = (form *)malloc(num * sizeof(form));
    if (forms == NULL)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }

    int count = 0;
    for (int i = s; i <= e && count < num; i++)
    {
        int a = i;
        for (int j = (-1)*(a-1); j <= abs(a) && count < num; j++)
        {
            int b = j;
            int c = pow(b, 2) - delta;
            // printf("Generated form: a = %d, b = %d, c = %d\n", a, b, c);

            if (c % (4 * a))
                continue;
            c /= (4 * a);
            forms[count++] = (form){a, b, c};
        }
    }
    // printf("\ncount = %d\n", count);

    if (count < num)
    {
        forms = (form *)realloc(forms, count * sizeof(form));
    }
    *ct = count;

    return forms;
}

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

form principal_form(int delta)
{
    form p_form;
    p_form.a = 1;
    int k = delta % 2;
    if (k < 0)
        k += 2;
    p_form.b = k;
    p_form.c = (pow(k, 2) - delta) / 4;
    printf("Principal form: (%d, %d, %d)\n", p_form.a, p_form.b, p_form.c);
    return p_form;
}

int gcd(int a, int b)
{
    while (b != 0)
    {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
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
    printf("Choose any integer value of n' for n = a + b * n':  "); // preferably 0
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
    int a = c_form->a; // 4
    int b = c_form->b; // 11
    int c = c_form->c; // 9

    if (b > ((-1) * a) && b <= a)
        return 0;

    if (a < 1)
        return 1;

    double num = ((double)(a - b)) / (2 * a);
    int r;
    if (num < 0)
    {
        r = (int)num - 1;
    }
    else
    {
        r = (int)num;
    }
    // printf("\nHELLO: num = %.2f r = %d\n", num, r);

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

int squared(form *c_form)
{
    Pair k_temp;
    int a = c_form->a;
    int b = c_form->b;
    int c = c_form->c;

    if (solve_congruence(b, &k_temp, c, a)) // 1, k, 6, 1 --->>> k.first=1 and k.second=1
        return 1;

    c_form->a = a * a;
    c_form->b = b - 2 * a * k_temp.first;
    c_form->c = (k_temp.first * k_temp.first) - ((b * k_temp.first) - c) / a;
    return 0;
}

// Returns true if n is a square free
// number, else returns false.
bool isSquareFree(int n)
{
    if (n % 2 == 0)
        n = n / 2;

    // If 2 again divides n, then n is
    // not a square free number.
    if (n % 2 == 0)
        return false;

    // n must be odd at this point.  So we can
    // skip one element (Note i = i +2)
    for (int i = 3; i <= sqrt(n); i = i + 2)
    {
        // Check if i is a prime factor
        if (n % i == 0)
        {
            n = n / i;

            // If i again divides, then
            // n is not square free
            if (n % i == 0)
                return false;
        }
    }

    return true;
}