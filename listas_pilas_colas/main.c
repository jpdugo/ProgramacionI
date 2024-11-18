
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// 350 colas  
// (* cabecera).dato es igual cabecera -> dato

// operaciones comunes 
// Inicializacion o creacion
// insertar
// eliminar
// Buscar
// recorrer
// comprobar si esta vacia

typedef double elemento;

typedef struct nodo
{
    elemento dato;
    struct nodo * siguiente;
} Nodo;

int main(void)
{
    
    srand(time(NULL));

    
    
   
    

    return 0;
}

// aca hago el transpaso del punterito
// Paso el doble puntero ya que quiero modificar la variable cabeza dentro de la funcion
// para llamar esta funcion hay que utilizar &Nodo para dar la direccion del memoria del puntero a
// elemento de tipo nodo  
void inserPrimero(Nodo **cabeza, elemento entrada) {
    Nodo *nuevo;
    nuevo = crearNodo(entrada);
    nuevo -> siguiente = *cabeza;
    *cabeza = nuevo;

}

Nodo * crearNodo(elemento x) {
    Nodo * p;
    p = (Nodo *)malloc(sizeof(Nodo));
    p -> dato = x;
    p -> siguiente = NULL;
    return p;
}



