// c program structure
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
  FILE *archivo = NULL;
  char *nombre = "programacion1.txt";
  char texto[30];

  archivo = fopen(nombre, "w");
  if (archivo == NULL)
  {
    printf("No se pudo abrir el archivo\n");
    exit(-1);
  }
  else
  {
    printf("Se abrio el archivo\n");
    printf("Ingrese el texto a guardar: ");
    fflush(stdin);
    gets(texto);
    fprintf(archivo, "%s", texto);
    fclose(archivo);
  }

  return 0;
}