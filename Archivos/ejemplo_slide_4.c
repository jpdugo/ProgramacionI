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

  printf("Ingrese una secuencia de numeros enteros:\n");
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
  while (fscanf(archivo_enteros, "%1d", &value) == 1 && i < MAX)
  {
    
    if (value % 2 == 0)
    {
      fprintf(archivo_resultados, "%d", value);
      contador_pares++;
    }
    i++;
  }

  rewind(archivo_resultados);
  
  char resultados[contador_pares];
  fgets(resultados, contador_pares + 1, archivo_resultados);
  
  printf("Hay %d numeros pares: %s", contador_pares, resultados);

  fclose(archivo_enteros);
  fclose(archivo_resultados);

  printf("\nFin del programa!");

  return 0;
}