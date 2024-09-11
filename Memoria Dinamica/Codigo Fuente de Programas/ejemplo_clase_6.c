#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct
{
  char nombre[20];
  char profesor[20];
  int nota;
} Materias;

void cargarDatos(Materias *M, int N);
void imprimirDatos(Materias *M, int N);

int main()
{
  Materias *M = NULL;
  int N = 2, i;

  M = (Materias *)malloc(N * sizeof(Materias));

  if (M == NULL)
  {
    printf("No se pudo reservar memoria\n");
    exit(-1);
  }
  else
  {
    printf("Se reservo memoria\n");

    cargarDatos(M, N);
    imprimirDatos(M, N);
    free(M);
  }

  return 0;
}

void cargarDatos(Materias *M, int N)
{
  int i;
  for (i = 0; i < N; i++)
  {
    printf("Ingrese el nombre de la materia: ");
    fflush(stdin);
    gets(M[i].nombre);

    printf("Ingrese el nombre del profesor: ");
    fflush(stdin);
    gets(M[i].profesor);

    printf("Ingrese la nota: ");
    scanf("%d", &M[i].nota);
  }
};

// void imprimirDatos(Materias *M, int N)
// {
//   int i;
//   for (i = 0; i < N; i++)
//   {
//     printf("Materia [%d]: %s\n", i + 1, M[i].nombre);
//     printf("Profesor: %s\n", M[i].profesor);
//     printf("Nota: %d\n", M[i].nota);
//   }
// }

void imprimirDatos(Materias *M, int N)
{
  int i;
  for (i = 0; i < N; i++)
  {
    printf("Materia [%d]: %s\n", i + 1, (M + i)->nombre);
    printf("Profesor: %s\n", (M + i)->profesor);
    printf("Nota: %d\n", (M + i)->nota);
  }
}
