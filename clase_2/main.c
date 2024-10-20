#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Programa AGENDA.
// � Hacer un programa que permita ingresar datos de contactos.
// � Arme un Array de estructuras (de 5 elementos, pero que pueda cambiarse f�cilmente �
// utilice #define).
// � El programa debe utilizar funciones y punteros a estructuras.
// � Programe una funci�n �ingresar Datos�, y otra �Imprimir datos�. Pase todos los valores por
// referencia.
// � Haga una tercera funci�n que permita buscar un nombre o un apellido. En caso de que se
// encuentre, muestre los datos en pantalla.
// � Todo este programa debe ser manejado mediante un men� de opciones.

#define SIZE 5

typedef struct
{
  char nombre[50];
  char apellido[50];
  int edad;
} Contacto;



typedef struct
{
  Contacto *contactos; // Puntero a un array de Contacto
  int contador;        // Contador para rastrear la cantidad de contactos
} Agenda;

void ingresar_datos(Agenda *p);
void mostrar_data(Agenda *p);
void buscar_contacto(Agenda *p);

int main()
{
  Contacto contactos[SIZE];
  Agenda agenda = {&contactos[0], 0};

  // Para debugear
  // strcpy(agenda.contactos -> nombre, "juan");
  // agenda.contador++;

  int c = 0;
  do
  {
    // system("CLS");
    printf("1. Ingresar Contactos\n");
    printf("2. Mostrar Contactos\n");
    printf("3. Buscar contactos\n");
    printf("4. Salir\n");
    scanf("%d", &c);
    switch (c)
    {
    case 1:
      fflush(stdin);
      ingresar_datos(&agenda);
      break;
    case 2:
      mostrar_data(&agenda);
      break;
    case 3:
      buscar_contacto(&agenda);
    }
  } while (c != 4);
  return 0;
}

void clearBuffer()
{
  int c;
  while ((c = getchar()) != '\n' && c != EOF);
} 

void ingresar_datos(Agenda *p)
{
  int pos = p->contador;
  printf("\nIngrese nombre del contacto:");
  clearBuffer();
  fflush(stdin);
  gets((p->contactos + pos)->nombre);

  printf("\nIngrese Apellido del contacto:");
  fflush(stdin);
  gets((p->contactos + pos)->apellido);

  printf("\nIngrese la edad del contacto:");
  fflush(stdin);
  scanf("%d", &(p->contactos + pos)->edad);

  (p->contador)++;
}

void mostrar_data(Agenda *p)
{
  system("CLS");
  printf("%d", p->contador);
  for (int i = 0; i < p->contador; i++)
  {
    printf("\nNombre: %s", (p->contactos + i)->nombre);
    printf("\nApellido: %s", (p->contactos + i)->apellido);
    printf("\nEdad: %d\n", (p->contactos + i)->edad);
  }
  system("PAUSE");
}

void buscar_contacto(Agenda *p)
{
  char busqueda[50];
  printf("\nIngrese una busqueda:\n");
  fflush(stdin);
  gets(busqueda);

  for (int i = 0; i < p->contador; i++)
  {
    if (strcmp(busqueda, (p->contactos + i)->nombre) == 0) // mejorar el algoritmo
    {
      printf("Hay match en el contacto %d: %s\n", i, (p->contactos + i)->nombre);
      system("PAUSE");
      return;
    }
  }

  printf("No hubo match\n");
}
