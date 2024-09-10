#include <stdio.h>
#include <stdlib.h>

// memoria dinamica ( heap o monticulo )
// malloc()
// calloc()
// realloc()
// free()

int* crearVector(int n);

int main()
{

  int *puntero = NULL;
  puntero = crearVector(5);

  printf("%d\n", *puntero);

  *puntero = 31;

  printf("%d\n", *puntero);

  free(puntero);

  printf("%d\n", *puntero);

  return 0;
}

// create a funtion that takes n as the length of a vector and returns its 
// memory address. Use malloc to allocate memory for the vector.
int* crearVector(int n) {
  int* vector = (int*)calloc(n, sizeof(int));
  if (vector == NULL) {
    printf("Failed to allocate memory.\n");
    exit(-1);
  }
  return vector;
}

