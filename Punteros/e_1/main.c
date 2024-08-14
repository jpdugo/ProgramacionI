#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
Dado un vector de 15 elementos enteros y aleatorios entre 0 y 100, se pide escribir un
programa en C (haciendo uso de punteros) que muestre las direcciones de memoria de
cada elemento del vector y su correspondiente valor. Ejemplo de salida:

Posici�n 0: Direccion de memoria: AABBCCDD � Valor: 20
Posici�n 1: Direccion de memoria: AABBCCDD � Valor: 44
Posici�n 2: Direccion de memoria: AABBCCDD � Valor: 12
Posici�n 3: Direccion de memoria: AABBCCDD � Valor: 32
*/

int main()
{
  int n, i, vector[10];
  int *p = NULL;

  srand(time(NULL));

  for (i = 0; i < 10; i++)
  {
    vector[i] = rand() % 101; // rand() % 101 genera n�meros entre 0 y 100

    p = &vector[i];
    printf("\nPosicion %d: Direccion de memoria: %p - Valor: %d", i, p, *p);
  }

  // graficar significa , hacerlo en papel
  return 0;
}
