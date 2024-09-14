#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR_SIZE 50

/**********************************************************
 *                                                        *
 *                        Estructuras                     *
 *                                                        *
 **********************************************************/

typedef struct
{
  char marca[MAX_CHAR_SIZE];
  char modelo[MAX_CHAR_SIZE];
  unsigned int cantidad_puertas;
} DatosAuto;

typedef struct
{
  char marca[MAX_CHAR_SIZE];
  DatosAuto datos_auto;
  unsigned int precio;
  unsigned int stock;
} Autos;

typedef struct
{
  char calle[MAX_CHAR_SIZE];
  unsigned int numero;
  char localidad[MAX_CHAR_SIZE];
} Direccion;

typedef struct
{
  char nombre[MAX_CHAR_SIZE];
  char apellido[MAX_CHAR_SIZE];
  Direccion direccion;
  unsigned int cantidad_autos;
  unsigned int presupuesto_anual;
} Clientes;

// puedo tener una cantidad no definida de autos y clientes al inicio del programa
typedef struct
{
  int cant_autos;
  int cant_clientes;
  Autos *autos;
  Clientes *clientes;
} Negocio;

/**********************************************************
 *                                                        *
 *               Definicion de Funciones                  *
 *                                                        *
 **********************************************************/

void cargar_auto(Negocio *negocio);
void visualizar_autos(Negocio *negocio);
void cargar_cliente(Negocio *p_negocio);
void visualizar_clientes(Negocio *negocio);
void visualizar_reporte_esp_clientes(Negocio *negocio);

/**********************************************************
 *                                                        *
 *                        Main                            *
 *                                                        *
 **********************************************************/

int main()
{
  int salir = 0, contador_autos = 0, opcion = 0;

  Negocio negocio;

  // contadores que se utilizan para agregar datos dinamicamente
  negocio.cant_autos = 0;
  negocio.cant_clientes = 0;

  // autos y clientes son punteros dentro del struct negocio
  negocio.autos = NULL;
  negocio.clientes = NULL;
  Negocio *p_negocio = NULL;
  p_negocio = &negocio;

  do
  {
    printf(
        "Ingrese una opcion:\n"
        "1. Cargar Autos\n"
        "2. Cargar Clientes\n"
        "3. Visualizar Autos en Stock\n"
        "4. Visualizar Clientes\n"
        "5. Reporte Especial Clientes\n"
        "6. Salir\n");
    scanf("%d", &opcion);
    switch (opcion)
    {
    case 1:
      cargar_auto(p_negocio);
      break;
    case 2:
      cargar_cliente(p_negocio);
      break;
    case 3:
      visualizar_autos(p_negocio);
      break;
    case 4:
      visualizar_clientes(p_negocio);
      break;
    case 5:
      visualizar_reporte_esp_clientes(p_negocio);
      break;
    case 6:
      salir++;
      break;
    default:
      system("read -p 'Comando erroneo, vuelva a ingresar un valor\n' var");
      break;
    }

    system("clear");

  } while (salir == 0);

  free(p_negocio->clientes);
  free(p_negocio->autos);
  free(p_negocio);

  return 0;
}

/**********************************************************
 *                                                        *
 *                        Funciones                       *
 *                                                        *
 **********************************************************/

void cargar_auto(Negocio *negocio)
{
  if (negocio->cant_autos > 4)
  {
    printf("Error, ha superado el maximo de autos que se pueden cargar: \n");
    system("read -p 'Presione la tecla enter para continuar...\n' var");
    return;
  }

  negocio->autos = (Autos *)realloc(negocio->autos, (negocio->cant_autos + 1) * sizeof(Autos));

  if (negocio->autos == NULL)
  {
    printf("No se pudo asignar\n\n");
    exit(-1);
  }

  int n = negocio->cant_autos; // para empezar desde el indice 0
  printf("Ingrese los Datos del Auto %d:\n", negocio->cant_autos + 1);

  printf("Marca:\n");
  fflush(stdin);
  gets(negocio->autos[n].marca);
  strcpy(negocio->autos[n].marca, negocio->autos[n].datos_auto.marca);

  printf("Modelo:\n");
  fflush(stdin);
  gets(negocio->autos[n].datos_auto.modelo);

  printf("Cantidad de Puertas:\n");
  fflush(stdin);
  scanf("%u", &negocio->autos[n].datos_auto.cantidad_puertas);

  printf("Precio:\n");
  fflush(stdin);
  scanf("%u", &negocio->autos[n].precio);

  printf("Stock:\n");
  fflush(stdin);
  scanf("%u", &negocio->autos[n].stock);

  negocio->cant_autos++;
}

void visualizar_autos(Negocio *negocio)
{
  // validar cuando no hay nada cargado
  for (int i = 0; i < negocio->cant_autos; i++)
  {
    if (negocio->autos[i].stock > 0)
    {
      printf("Auto %d:\n", i + 1);
      printf("Marca %s: \n", negocio->autos[i].marca);
      printf("datos auto -> marca %s: \n", negocio->autos[i].datos_auto.marca);
      printf("datos auto -> modelo %s: \n", negocio->autos[i].datos_auto.marca);
      printf("datos auto -> cantidad de puertas %u: \n", negocio->autos[i].datos_auto.cantidad_puertas);
      printf("Precio %u: \n", negocio->autos[i].precio);
      printf("Stock %u: \n\n", negocio->autos[i].stock);
    }
  }
  system("read -p 'Presione la tecla enter para continuar...\n' var");
}

void cargar_cliente(Negocio *negocio)
{

  if (negocio->cant_clientes > 4)
  {
    printf("Error, ha superado el maximo de clientes que se pueden cargar: \n");
    system("read -p 'Presione la tecla enter para continuar...\n' var");
    return;
  }

  negocio->clientes = (Clientes *)realloc(negocio->clientes, (negocio->cant_clientes + 1) * sizeof(Clientes));

  if (negocio->clientes == NULL)
  {
    printf("No se pudo asignar\n\n");
    exit(-1);
  }

  printf("Para el cliente %d ingrese:\n", negocio->cant_clientes + 1);
  printf("Apellido:\n");
  fflush(stdin);
  gets(negocio->clientes[negocio->cant_clientes].apellido);

  printf("Nombre:\n");
  fflush(stdin);
  gets(negocio->clientes[negocio->cant_clientes].nombre);

  printf("Direccion -> Calle:\n");
  fflush(stdin);
  gets(negocio->clientes[negocio->cant_clientes].direccion.calle);

  printf("Direccion -> Numero:\n");
  fflush(stdin);
  scanf("%u", &negocio->clientes[negocio->cant_clientes].direccion.numero);

  printf("Direccion -> Localidad:\n");
  fflush(stdin);
  gets(negocio->clientes[negocio->cant_clientes].direccion.localidad);

  printf("Cantidad de Autos:\n");
  fflush(stdin);
  scanf("%u", &negocio->clientes[negocio->cant_clientes].presupuesto_anual);

  printf("Presupuesto Anual:\n");
  fflush(stdin);
  scanf("%u", &negocio->clientes[negocio->cant_clientes].cantidad_autos);

  negocio->cant_clientes++;
}

void visualizar_clientes(Negocio *negocio)
{
  for (int i = 0; i < negocio->cant_clientes; i++)
  {
    printf("Cliente %d:\n", i + 1);
    printf("Apellido %s\n", negocio->clientes[i].apellido);
    printf("Nombre: %s\n", negocio->clientes[i].nombre);
    printf("Direccion:\n");
    printf("- Calle: %s\n", negocio->clientes[i].direccion.calle);
    printf("- Numero: %u\n", negocio->clientes[i].direccion.numero);
    printf("- Localidad: %s\n", negocio->clientes[i].direccion.localidad);
    printf("Cantidad de Autos: %u\n", negocio->clientes[i].cantidad_autos);
    printf("Presupuesto Anual: %u\n\n", negocio->clientes[i].presupuesto_anual);
  }

  system("read -p 'Presione la tecla enter para continuar...\n' var");
}

void visualizar_reporte_esp_clientes(Negocio *negocio)
{

  for (int i = 0; i < negocio->cant_clientes; i++)
  {
    if (negocio->clientes[i].cantidad_autos > 2 && negocio->clientes[i].presupuesto_anual >= 2000000)
    {
      printf("Cliente %d:\n", i + 1);
      printf("Apellido %s\n", negocio->clientes[i].apellido);
      printf("Nombre: %s\n", negocio->clientes[i].nombre);
      printf("Direccion:\n");
      printf("- Calle: %s\n", negocio->clientes[i].direccion.calle);
      printf("- Numero: %u\n", negocio->clientes[i].direccion.numero);
      printf("- Localidad: %s\n", negocio->clientes[i].direccion.localidad);
      printf("Cantidad de Autos: %u\n", negocio->clientes[i].cantidad_autos);
      printf("Presupuesto Anual: %u\n\n", negocio->clientes[i].presupuesto_anual);
    }
  }

  system("read -p 'Presione la tecla enter para continuar...\n' var");
}
