#include <stdio.h>
#include <stdlib.h>

int main()
{
  FILE *archivo = NULL;
  char texto[50];

  if((archivo = fopen("Programacion1.txt", "w")) == NULL) {
    printf("Error al abrir el archivo\n");
    return -1;
  }

  printf("%d \n", ferror(archivo));

  printf("Ingrese una cadena de texto:\n");
  fflush(stdin);

  scanf(" %[^\n]", texto);

  fprintf(archivo, "%s\n", texto);

  if (ferror(archivo)) {
    perror("Error occurred");
  }

  fclose(archivo);

  printf("Fin del archivo!");

  return 0;
}