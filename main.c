#include "helper.h"

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

    return 0;
}
