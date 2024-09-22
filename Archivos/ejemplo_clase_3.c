#include <stdio.h>
#include <stdlib.h>

// ejemplo fwrite()

int main()
{

  FILE *archivo1 = NULL;
  char *nombrearchivo = "ejemplo_3.txt";
  char texto[50];

  archivo1 = fopen(nombrearchivo, "ab"); // abro archivo para escritura en binario

  if (archivo1 == NULL)
  {
    printf("Error al abrir el archivo\n");
    return -1;
  }

  printf("Ingrese una cadena de texto: \n");
  fflush(stdin);
  scanf(" %[^\n]", texto);

  fwrite(&texto, sizeof(char), 50, archivo1);
  fclose(archivo1);

  printf("\n\nFin del programa. Ver el archivo\n\n");

  printf("Ahora leo el archivo...");

  archivo1 = fopen(nombrearchivo, "rb");
  
  while(fread(&texto, sizeof(char), 50, archivo1) > 0) {
    printf(" %s\n", texto);
  }
  return 0;
}