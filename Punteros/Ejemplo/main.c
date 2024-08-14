#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n;
    int suma, resta, multiplicacion, division;
    int *p = NULL;
    int *q = NULL;

    printf("\n Ingrese valor para n: ");
    scanf("%d", &n);

    p = &n;

    printf("\nEl valor de n es : %d\n", n);
    printf("\nEl valor de p (direccion de n) es %p\n\n", p);
    printf(" p apunta a la direccion de n, que contiene el valor (*p) = : %d\n", *p);

    suma = 200 + *p;
    resta = 200 - *p;
    multiplicacion = 200 * (*p);
    division = 200 / (*p);

    printf("\nSUMA = %d", suma);
    printf("\nResta = %d", resta);
    printf("\nMultiplicacion = %d", multiplicacion);
    printf("\nDivision = %d", division);

    q = &p;

    printf("\%d", *q);

    return 0;
}
