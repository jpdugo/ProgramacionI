#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 20

int main()
{
  FILE *archivo_enteros = NULL;
  FILE *archivo_resultados = NULL;
  char texto[MAX];
  int contador_pares = 0;

  if ((archivo_enteros = fopen("enteros.txt", "w+")) == NULL)
  {
    printf("Error al abrir el archivo\n");
    return -1;
  }

  printf("%d \n", ferror(archivo_enteros));

  printf("Ingrese una secuencia de numeros enteros separados por un espacio:\n");
  fflush(stdin);
  scanf(" %[^\n]", texto);
  fprintf(archivo_enteros, "%s\n", texto);

  if (ferror(archivo_enteros))
  {
    perror("Error occurred");
  }

  rewind(archivo_enteros);

  int i = 0;
  int value;
  archivo_resultados = fopen("resultados.txt", "w+");
  while (fscanf(archivo_enteros, "%d ", &value) == 1 && i < MAX)
  { 
    if (value % 2 == 0)
    {
      fprintf(archivo_resultados, "%d ", value);
      contador_pares++;
    }
    i++;
  }

  rewind(archivo_resultados);
  
  int * resultados = (int*) malloc(contador_pares * sizeof(int)); // usar  malloc para esto
  if (resultados == NULL) {
    perror("Unable to allocate memory");
    exit(EXIT_FAILURE);
  }

  printf("Hay %d numeros pares: ", contador_pares);

  i = 0;
  while (fscanf(archivo_resultados, "%d", resultados + i) != EOF) {
    printf("%d ", *(resultados + i));
    i++;
  }

  fclose(archivo_enteros);
  fclose(archivo_resultados);

  printf("\nFin del programa!");

  return 0;
}