#ifndef HELPER_H
#define HELPER_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <stdbool.h>
typedef struct
{
    int a;
    int b;
    int c;
} form;

typedef struct
{
    int first;
    int second;
} Pair;

form *gen_forms(int delta, int num, int *ct);
Pair extended_gcd(int a, int b);
form principal_form(int delta);
int gcd(int a, int b);
int solve_congruence(int a, Pair *x, int b, int m);
int composed(form *a_form, form *b_form, form *c_form);
int normalized(form *c_form);
int reduced(form *c_form);
int squared(form *c_form);
bool isSquareFree(int n);
int pow_n(form *f, int n);

#endif