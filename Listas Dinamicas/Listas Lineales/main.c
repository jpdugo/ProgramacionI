#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct 
{
    char nombre;
    int valor;
} Dato;

typedef struct s 
{
    Dato elemento;
    struct s *siguiente;
} ElementoLista;

void error();

int main()
{
    
    return 0;
}

void error()
{
    printf("Insuficiente memoria\n");
    exit(1);
}