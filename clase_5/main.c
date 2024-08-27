#include <stdio.h>
#include <stdlib.h>

// memoria dinamica ( heap o monticulo )
// malloc()
// calloc()
// realloc()
// free()

int main()
{

  int *puntero = NULL;
  puntero = (int *)malloc(sizeof(int));

  if (puntero == NULL)
  {
    exit(-1);
  }
  else
  {
    printf("%d\n", *puntero);
  }

  *puntero = 31;

  printf("%d\n", *puntero);


  free(puntero);

  printf("%d\n", *puntero);

  return 0;
}
