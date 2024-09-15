#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// hacer practica final y el ejercico 7 de punteros

#define TOPE 10

// function protoypes
int *completar_vector(int *largo);
void imprimir_vector(int vector[], int *largo);

int main()
{
  int tope_value = TOPE;
  int *tope = &tope_value;

  int *vector = completar_vector(tope);
  printf("Vector sin ordenar: ");
  imprimir_vector(vector, tope);

  int intervalo = *tope / 2;
  while (intervalo > 0)
  {

    for (int i = intervalo; i < *tope; i++)
    {
      int j = i - intervalo;
      while (j >= 0)
      {
        int k = j + intervalo;
        if (vector[j] > vector[k])
        {
          j = -1;
        }
        else
        {
          int temp;
          temp = vector[j];
          vector[j] = vector[k];
          vector[k] = temp;
          j -= intervalo;
        }
      }
    }

    intervalo = intervalo / 2;
  }

  printf("Vector ordenado: ");
  imprimir_vector(vector, tope);

  free(vector);

  return 0;
}

int *completar_vector(int *largo)
{
  int *vector = (int *)malloc(*largo * sizeof(int));

  srand(time(NULL));

  for (int i = 0; i < *largo; i++)
  {
    vector[i] = rand() % 101;
  }

  return vector;
}

void imprimir_vector(int vector[], int *largo)
{
  for (int i = 0; i < *largo - 1; i++)
  {
    printf("%d - ", vector[i]);
  }

  printf("%d\n", vector[*largo - 1]);
}
