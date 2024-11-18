#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 5

typedef struct {
    int ID_consecionaria;
    char nombre_consecionaria[20];
    char direccion[20];
    char gerente[20];
    float ventas;
} Consecionaria;

typedef struct {
    int ID_pedidos;
    Consecionaria con;
    char marca[20];
    char modelo[20];
    float precio;
    char estado[20];
} Pedidos;

typedef struct Elemento {
    Pedidos p;
    struct Elemento *siguiente;
} Nodo;

typedef struct {
    Nodo *frente;
    Nodo *final;
} Cola;

void inicializar_cola(Cola *cola);
void encolar(Cola *cola, Pedidos x);
void desencolar(Cola *cola);
void mostrar_pedidos_encolados(Cola cola);
int colaVacia(Cola cola);
Pedidos ingresar_pedido(Cola cola);
void liberar_cola(Cola *cola);
void guardar_cola(Cola *cola, const char *nombre_archivo);
void cargar_cola(Cola *cola, const char *nombre_archivo);
void buscar_pedido(Cola cola_encolados,Cola cola_entregados,char *nombre_encolados,char *nombre_entregados);
void concesionarias(Cola cola,char *nombre_entregados);

int id_consecionaria = 0;
int id_pedido = 1000;


int main() {
    Cola micola, entregados;
    inicializar_cola(&micola);
    inicializar_cola(&entregados);


    Pedidos pedido;
    int contador_encolados=0;  //Para saber que numero de pedido va a tener el siguiente
    int contador_entregados=0;
    int contador_concesionarias=0;
    FILE *archivo_entregados=NULL;
    char *nombre_archivo="entregados.bin";

    FILE *archivo_encolados=NULL;
    char *nombre_encolados="pendientes.bin";

    archivo_encolados=fopen(nombre_encolados,"rb");
    if(archivo_encolados==NULL)
    {
        printf("A");
    }else
    {
        while (fread(&pedido, sizeof(Pedidos), 1, archivo_encolados)) {
        contador_encolados++;
    }

    fclose(archivo_encolados);
    }

    archivo_entregados=fopen(nombre_archivo,"rb");
    if(archivo_entregados==NULL)
    {
        printf("A");
    }else
    {
        while (fread(&pedido, sizeof(Pedidos), 1, archivo_entregados)) {
        contador_entregados++;
    }

    fclose(archivo_entregados);
    }


    id_pedido+=(contador_encolados +contador_entregados);

    cargar_cola(&micola,nombre_encolados);
    cargar_cola(&entregados,nombre_archivo);



    printf("Bienvenido!");

    int opc;
    do {
        printf("\n");
        system("pause");
        system("cls");
        printf("1) Encolar\n");
        printf("2) Desencolar\n");
        printf("3) Reporte de pedidos en cola\n");
        printf("4) Reporte pedidos finalizados\n");
        printf("5) Buscar pedido\n");
        printf("6) Salir del programa\n");
        printf("Opcion: ");
        scanf("%d", &opc);
        system("cls");

        switch (opc) {
        case 1: {
            Pedidos p = ingresar_pedido(micola);
            encolar(&micola, p);
        } break;
        case 2:
            if (!colaVacia(micola)) {

                strcpy(micola.frente->p.estado,"entregado");
                encolar(&entregados, micola.frente->p);
                desencolar(&micola);
            } else {
                printf("\nNo hay pedidos en la cola.\n");
            }
            break;
        case 3:
            mostrar_pedidos_encolados(micola);
            break;
        case 4:
            mostrar_pedidos_encolados(entregados);
            break;
        case 5:
            buscar_pedido(micola,entregados,nombre_encolados,nombre_archivo);
            break;
        case 6:
            guardar_cola(&micola, nombre_encolados);
            guardar_cola(&entregados, nombre_archivo);
            liberar_cola(&micola);
            liberar_cola(&entregados);
            printf("Saliendo del programa...\n");
            break;
        default:
            printf("N˙mero fuera de rango.\n");
        }
    } while (opc != 6);

    return 0;
}

void inicializar_cola(Cola *cola) {
    cola->frente = NULL;
    cola->final = NULL;
}

void encolar(Cola *cola, Pedidos x) {
    Nodo *nuevo = malloc(sizeof(Nodo));
    nuevo->p = x;
    nuevo->siguiente = NULL;

    if (colaVacia(*cola)) {
        cola->frente = nuevo;
        cola->final = nuevo;
    } else {
        cola->final->siguiente = nuevo;
        cola->final = nuevo;
    }
}

int colaVacia(Cola cola) {
    return cola.frente == NULL;
}

void desencolar(Cola *cola) {
    if (colaVacia(*cola)) {
        printf("\nLa cola est· vacÌa.\n");
        return;
    }

    Nodo *temp = cola->frente;
    cola->frente = cola->frente->siguiente;

    if (cola->frente == NULL) {
        cola->final = NULL;
    }

    free(temp);
}

Pedidos ingresar_pedido(Cola cola) {
    Pedidos x;

    id_pedido++;
    x.ID_pedidos = id_pedido;

    printf("Datos de la consecionaria: ");
    printf("\n\tNombre de la consecionaria: ");
    fflush(stdin);
    gets(x.con.nombre_consecionaria);
    printf("\tDirecciÛn: ");
    fflush(stdin);
    gets(x.con.direccion);
    printf("\tNombre del gerente: ");
    fflush(stdin);
    gets(x.con.gerente);

    int encontrado = 0;
    Nodo *temp = cola.frente;
    while (temp != NULL && !encontrado) {
        if (strcmp(temp->p.con.nombre_consecionaria, x.con.nombre_consecionaria) == 0) {
            x.con.ID_consecionaria = temp->p.con.ID_consecionaria;
            encontrado = 1;
        }
        temp = temp->siguiente;
    }

    if (!encontrado) {
        id_consecionaria++;
        x.con.ID_consecionaria = id_consecionaria;
    }

    printf("\nDatos del pedido:");
    printf("\n\tMarca: ");
    fflush(stdin);
    gets(x.marca);
    printf("\tModelo: ");
    fflush(stdin);
    gets(x.modelo);
    printf("\tPrecio: ");
    scanf("%f", &x.precio);
    strcpy(x.estado, "espera");

    return x;
}

void mostrar_pedidos_encolados(Cola cola) {
    Nodo *temp = cola.frente;
    int contador = 1;

    if (colaVacia(cola)) {
        printf("No hay pedidos en cola.\n");
        return;
    }

    while (temp != NULL) {
        printf("Pedido %d:\n", contador++);
        printf("\tID del pedido: %d\n", temp->p.ID_pedidos);
        printf("\tMarca: %s\n", temp->p.marca);
        printf("\tModelo: %s\n", temp->p.modelo);
        printf("\tPrecio: %.2f\n", temp->p.precio);
        printf("\tEstado: %s\n", temp->p.estado);
        printf("\tID concesionaria: %d\n", temp->p.con.ID_consecionaria);
        printf("\tConcesionaria: %s\n", temp->p.con.nombre_consecionaria);
        printf("\tGerente: %s\n", temp->p.con.gerente);
        printf("\n-----------------------\n");
        temp = temp->siguiente;
    }
}

void liberar_cola(Cola *cola) {
    while (!colaVacia(*cola)) {
        desencolar(cola);
    }
}

void guardar_cola(Cola *cola, const char *nombre_archivo) {
    FILE *archivo = fopen(nombre_archivo, "wb");
    if (!archivo) {
        perror("\nError al abrir archivo para guardar cola");
        return;
    }

    Nodo *temp = cola->frente;
    while (temp != NULL) {
        fwrite(&(temp->p), sizeof(Pedidos), 1, archivo);
        temp = temp->siguiente;
    }
    fclose(archivo);
}

void cargar_cola(Cola *cola, const char *nombre_archivo) {
    FILE *archivo = fopen(nombre_archivo, "rb");
    if (!archivo) {
        printf("\nArchivo %s no encontrado. Iniciando cola vacia.\n", nombre_archivo);
        return;
    }

    Pedidos pedido;
    while (fread(&pedido, sizeof(Pedidos), 1, archivo)) {
        encolar(cola, pedido);
    }
    fclose(archivo);
}

void buscar_pedido(Cola cola_encolados,Cola cola_entregados,char *nombre_encolados,char *nombre_entregados)
{
    int opc;
    printf("Ingrese el ID del pedido a buscar: ");
    scanf("%d",&opc);

    Pedidos pedido;
    int encontrado=0;

    Nodo* temp_encolados;
    temp_encolados=cola_encolados.frente;

    Nodo * temp_entregados;
    temp_entregados=cola_entregados.frente;


    while((temp_encolados!=NULL) && (!encontrado))
    {
        if(temp_encolados->p.ID_pedidos==opc)
        {
            printf("El pedido con ID %d esta encolado",opc);
            encontrado=1;
        }
        else
        {
            temp_encolados=temp_encolados->siguiente;
        }
    }

    if(!encontrado)
    {
        while((temp_entregados!=NULL) && (!encontrado))
        {
            if(temp_entregados->p.ID_pedidos==opc)
            {
                printf("El pedido %d fue entregado",opc);
                encontrado=1;
            }
            else
            {
                temp_entregados=temp_entregados->siguiente;
            }
        }
    }

    if(!encontrado)
    {

        FILE *archivo_entregados=fopen(nombre_entregados,"rb");
        if(archivo_entregados==NULL)
        {
            printf("\nNo se ha encontrado el archivo de pedidos entregados");
        }else
        {
            while (fread(&pedido, sizeof(Pedidos), 1, archivo_entregados) && (!encontrado))
            {
                if(pedido.ID_pedidos==opc)
                {
                    printf("\nEl pedido con ID %d ya fue entregado",opc);
                    encontrado=1;

                }
            }
        }
        fclose(archivo_entregados);
    }

    if(!encontrado)
    {
        printf("\nNo existe ningun pedido con ese ID");
    }
}

void concesionarias(Cola cola,char *nombre_entregados)
{
    Pedidos p;
    FILE *archivo_entregados=fopen(nombre_entregados,"rb");
    if(archivo_entregados==NULL)
    {
        printf("\nNo se ha encontrado el archivo de pedidos en espera");
        return;
    }

    //while(fread(&p,sizeof(Pedidos),1,archivo_entregados))
    //{


    //}




}
