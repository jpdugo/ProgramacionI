#include <stdio.h>
#include <stdlib.h>

// Hacer un programa que permita sumar dos valores tipo float (introducidos por teclado).
// Para realizar la suma, utilice aritm�tica de punteros.

// declarar dos punteros
int main()
{
  float num[2], suma;
  float *p = NULL;

  printf("Introduce dos floats\n");

  scanf("%f", &num[0]); // hay que tener en cuenta que cuando tenes un puntero y usas scanf , vas sin ponerle ampersum
  scanf("%f", &num[1]);

  p = &num[0];

  printf("La suma es: %f", *p + *(p + 1));

  return 0;
}
