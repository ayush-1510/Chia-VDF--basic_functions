#ifndef HELPER_H
#define HELPER_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

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

int gcd(int a, int b);
Pair extended_gcd(int a, int b);
int solve_congruence(int a, Pair *x, int b, int m);
int composed(form *a_form, form *b_form, form *c_form);
int normalized(form *c_form);
int reduced(form *c_form);

#endif