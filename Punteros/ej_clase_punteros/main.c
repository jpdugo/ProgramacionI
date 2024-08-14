#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Hacer un programa que permita llenar un vector de 10 posiciones con numeros aleatorios entre 0 y 20
// Declarar 2 punteros (puntero 1 y 2)
// imprimir el vector en pantalla, y luego, cada vez que se presione la barra espaciadora system("pause"); se debe incrementar en 1 el puntero1, y...
// decrementar en 1 el puntero 2
// Ir imprimiento en pantalla los valores obtenidos mediante indireccion

int main()
{
  int n, i, vector[10];
  int *puntero1 = NULL;
  int *puntero2 = NULL;

  srand(time(NULL));

  for (i = 0; i < 10; i++)
  {
    vector[i] = rand() % 21; // rand() % 21 genera n�meros entre 0 y 20
    printf("%d, ", vector[i]);
  }

  puntero1 = &vector[0];
  puntero2 = &vector[9];

  // Aritmetica de punteros

  for (i = 0; i < 10; i++)
  {

    printf("\npuntero1: %d\n", *puntero1);
    printf("puntero2: %d\n\n", *puntero2);

    puntero1++;
    puntero2--;
    system("pause");
  }

  return 0;
}
