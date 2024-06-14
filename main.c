#include "helper.h"

int32_t main()
{
    srand(time(NULL));
    int delta, d;
    printf("Enter the Integer and square free value of d for binary quadratic forms (positive, preferably prime): ");
    scanf("%d", &d);
    delta = -d;
    printf("Delta = %d\n", delta);
    if (delta >= 0)
    {
        printf("Error: Delta must be less than 0.\n");
        return 1;
    }
    else if ((delta % 4)+4 == 2 || (delta % 4)+4 == 3)
    {
        printf("Error: Delta must be congruent to 0 or 1 modulo 4.\n");
        return 1;
    }
    else if (!isSquareFree(d))
    {
        printf("Error: Delta must be square free.\n");
        return 1;
    }

    // form p_form = principal_form(delta);
    int num;
    printf("Number of positive definite forms required? ");
    scanf("%d", &num);
    int ct;
    form *forms = gen_forms(delta, num, &ct);
    printf("\nGenerated %d forms:\n", ct);
    for (int i = 0; i < ct; i++)
    {
        if (forms[i].a == 1 && forms[i].b == abs(delta)%2)
        {
            printf("forms[%d] (Principal Form): a = %d, b = %d, c = %d\n", i, forms[i].a, forms[i].b, forms[i].c);
            continue;
        }
        printf("forms[%d]: a = %d, b = %d, c = %d\n", i, forms[i].a, forms[i].b, forms[i].c);
    }

    int i, j;
    printf("Give two indices of forms to proceed with composition:\n");
    scanf("%d %d", &i, &j);
    // form e_form = {2,1,3};
    // printf("\nExample form: (%d, %d, %d)", e_form.a, e_form.b, e_form.c);

    // COMPOSITION
    form c_form;
    if (composed(&forms[i], &forms[j], &c_form))
    {
        printf("\nFAILED COMPOSITION");
        return 0;
    }
    else
        printf("Composed form: (%d, %d, %d)", c_form.a, c_form.b, c_form.c);

    // NORMALIZATION
    if (normalized(&c_form))
    {
        printf("\nFAILED NORMALIZATION");
        return 0;
    }
    else
        printf("\nNormalized form: (%d, %d, %d)", c_form.a, c_form.b, c_form.c);

    // REDUCTION
    while (reduced(&c_form));

    printf("\nReduced form: (%d, %d, %d)", c_form.a, c_form.b, c_form.c);
    printf("\nInverse of form: (%d, %d, %d)", c_form.a, -c_form.b, c_form.c);

    // SQUARING
    if (squared(&c_form))
    {
        printf("\nFAILED Squaring");
        return 0;
    }
    else
        printf("\nSquared form: (%d, %d, %d)", c_form.a, c_form.b, c_form.c);

    // REDUCTION
    while (reduced(&c_form));
    printf("\nReduced form after squaring: (%d, %d, %d)", c_form.a, c_form.b, c_form.c);

    // INVERSE
    printf("\nInverse of form after squaring: (%d, %d, %d)", c_form.a, -c_form.b, c_form.c);

    // EXPONENTIATION
    int n;
    form temp;
    printf("\nEnter the values (a, b, c) for the form whose exponent you want to calculate: ");
    scanf("%d %d %d", &temp.a, &temp.b, &temp.c);
    printf("Enter the exponent for this form: ");
    scanf("%d", &n);
    if (pow_n(&temp, n))
    {
        printf("\nFAILED Exponentiation");
        return 0;
    }
    else
    {
        reduced(&temp);
        printf("\nForm after exponentiation: (%d, %d, %d)", temp.a, temp.b, temp.c);
    }

    return 0;
}
