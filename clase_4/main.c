#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// hacer practica final y el ejercico 7 de punteros

#define TOPE 10

// function protoypes
void completar_vector(int vector[], int largo);
void imprimir_vector(int vector[], int largo);

int main()
{

  int vector[TOPE];
  completar_vector(vector, TOPE);
  imprimir_vector(vector, TOPE);

  int intervalo = TOPE / 2;
  while (intervalo > 0)
  {

    for (int i = intervalo; i < TOPE; i++)
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

  imprimir_vector(vector, TOPE);

  return 0;
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

