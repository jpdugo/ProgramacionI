#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct elemento {
    int a;
    int b;
} Elemento;

typedef struct nodo {
    Elemento dato;
    struct nodo * siguiente;
} Nodo;

typedef struct cola {
    Nodo * frente;
    Nodo * final;
} Cola;

int main() {
    // Your code here

    return 0;
}

Cola * crearCola() {
    Cola * cola;
    cola = (Cola*)malloc(sizeof(Cola));
    cola ->final = cola -> frente = NULL;
    return cola;
}

Nodo * crearNodo(entrada) {
    Nodo * nodo;
    nodo = (Nodo*)malloc(sizeof(Nodo));
    (nodo -> dato).a = entrada;
    (nodo -> dato).a = entrada;
    nodo -> siguiente = NULL;
    return nodo;
}

void insertar(Cola * cola, Elemento entrada) {
    // me fijo si la cola esta vacia, en ese caso inserto en el frente 
    // otherwise inserto en el final
}

Elemento quitar(Cola * cola) {
    
}

