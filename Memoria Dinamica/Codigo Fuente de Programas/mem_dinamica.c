/*

Ejemplo con malloc, realloc y free

*/

#include <stdio.h>
#include <stdlib.h>

  int main()
  {
    int i;
    int * vector1=NULL;
    int * vector_nuevo=NULL;

    vector1 = malloc(10*sizeof(int));
    if (vector1==NULL)
    {
        printf("No se pudo asignar\n\n");
        return 0;
    }
      else
        printf("Se asigno correctamente el espacio en memoria...\n");

    for (i=0;i<10;i++)
    {
        vector1[i]=i+1;
        printf("\nen la posicion %d el valor es: %d ", i, vector1[i]);
    }
printf("\n\n");
system("pause");

  //Implemento realloc para tener mas espacio
  vector_nuevo=realloc(vector1, 14*sizeof(int));

  //Verifico que se pudo reasignar memoria
  if (vector_nuevo==NULL)
    {
        printf("No se pudo asignar\n\n");
        return 0;
    }
      else
        printf("Se asigno correctamente el espacio en memoria...\n");

  for (i=0;i<14;i++)
    {
        printf("\nen la posicion %d el valor ampliado es: %d ", i, vector_nuevo[i]);
    }
printf("\n\n\nAhora libero la memoria.....\n");
  system("pause");

 //ahora libero la memoria y veo cÛmo quedÛ

 free(vector_nuevo);

  for (i=0;i<14;i++)
    {
        printf("\nen la posicion %d el valor ampliado es: %d ", i, vector_nuevo[i]);
    }

  printf("\n\n\nMemoria liberada.....\n");
  system("pause");

  //vuelvo a dejar en NULL Los punteros....
  vector1=NULL;
  vector_nuevo=NULL;
  }

