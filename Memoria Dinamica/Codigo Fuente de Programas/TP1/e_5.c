#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
  char nombre[20];
  char apellido[20];
  int edad;
  int dni;
} Persona;

int main() {
  int N;
  Persona *p = NULL;

  printf("Ingrese la cantidad de personas: ");
  
  scanf("%d", &N);

  p = (Persona *)malloc(N * sizeof(Persona));

  if (p == NULL) {
    printf("No se pudo reservar memoria\n");
    exit(-1);
  } else {
    printf("Se reservo memoria\n");

    for (int i = 0; i < N; i++) {
      printf("Ingrese el nombre de la persona %d: ", i + 1);
      fflush(stdin);
      gets(p[i].nombre);

      printf("Ingrese el apellido de la persona %d: ", i + 1);
      fflush(stdin);
      gets(p[i].apellido);

      printf("Ingrese la edad de la persona %d: ", i + 1);
      scanf("%d", &p[i].edad);

      printf("Ingrese el DNI de la persona %d: ", i + 1);
      scanf("%d", &p[i].dni);
    }

    for (int i = 0; i < N; i++) {
      printf("Nombre: %s\n", (p + i)->nombre);
      printf("Apellido: %s\n", (p + i)->apellido);
      printf("Edad: %d\n", (p + i)->edad);
      printf("DNI: %d\n", (p + i)->dni);
    }

    free(p);
  }

  
  return 0;
}