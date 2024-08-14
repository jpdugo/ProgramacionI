#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// rearmar con punteros

#define TOPE 10

void completar_vector(int vector[], int largo);
void imprimir_vector(int vector[], int largo);
void ordenar_burbuja(int vector[], int largo);

int main()
{
  int vector[TOPE];
  completar_vector(vector, TOPE);
  ordenar_burbuja(vector, TOPE);
  imprimir_vector(vector, TOPE);
  return 0;
}

void ordenar_burbuja(int vector[], int largo)
{

  int temp;
  int finalizar_temprano = 0;

  for (int j = largo - 1; j > 0; j--)
  {

    finalizar_temprano = 1;
    for (int i = 0; i < j; i++)
    {
      temp = vector[i + 1];

      if (vector[i] > vector[i + 1])
      {
        finalizar_temprano = 0;
        vector[i + 1] = vector[i];
        vector[i] = temp;
        // imprimir_vector(vector, largo);
      }
    }
    if (finalizar_temprano)
    {
      printf("El vector ya se encuentra ordenado tomando como tope %d\n", j);
      return;
    }
  }
}

void completar_vector(int vector[], int largo)
{
  srand(time(NULL));

  for (int i = 0; i < largo; i++)
  {
    vector[i] = rand() % 101;
  }
}

void imprimir_vector(int vector[], int largo)
{
  for (int i = 0; i < largo - 1; i++)
  {
    printf("%d - ", vector[i]);
  }

  printf("%d\n", vector[largo - 1]);
}
