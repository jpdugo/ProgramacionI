#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {              //Struct de la concesionaria
    int ID_concesionaria;
    char nombre_concesionaria[20];
    char direccion[20];
    char gerente[20];
    float ventas;
} Concesionaria;

typedef struct {              //Struct del pedido(Esta anidado con el struct de concesionaria)
    int ID_pedidos;
    Concesionaria con;
    char marca[20];
    char modelo[20];
    float precio;
    char estado[20];
} Pedidos;

typedef struct Elemento {     //Elementos de cada nodo de la lista enlazada
    Pedidos p;
    struct Elemento *siguiente;
} Nodo;

typedef struct {              //Struct de la cola donde se van a ir encolando los nodos
    Nodo *frente;
    Nodo *final;
} Cola;

void inicializar_cola(Cola *cola);
void encolar(Cola *cola, Pedidos x);
void desencolar(Cola *cola);

void mostrar_pedidos_encolados(Cola cola);
int colaVacia(Cola cola);
Pedidos ingresar_pedido(Cola cola,Cola cola_entreados);

void liberar_cola(Cola *cola);
void guardar_cola(Cola *cola, char *nombre_archivo);
void cargar_cola(Cola *cola,  char *nombre_archivo);

void buscar_pedido(Cola cola_encolados,Cola cola_entregados);
void concesionarias(Cola cola_encolados,Cola cola_entregados);

int id_concesionaria = 0; //Para tener conteo de cuantas consecionarias hay
int id_pedido = 1000;     //Para tener conteo de cuantos pedidos hay

int main() {

    Cola micola, entregados;  //Estas dos colas van hacer las que van a guardar los pedidos encolados y los entregados
    inicializar_cola(&micola); //Inicializamos las dos colas
    inicializar_cola(&entregados);


    int contador_encolados=0;  //Para saber que numero de pedido va a tener el siguiente pedido a la hora de volver a cargar el programa
    int contador_entregados=0;

    int contador_concesionarias=0; //Para saber porque concesionaria va a a la hora de volver a cargar el programa

    FILE *archivo_entregados=NULL;
    char *nombre_archivo="entregados.bin";

    FILE *archivo_encolados=NULL;             //Creo los dos archivo binarios donde se van a guardar
    char *nombre_encolados="pendientes.bin";  //los datos de cada una de las listas a la hora de cerrar el programa

    cargar_cola(&micola,nombre_encolados);  //Enlazo los datos que tenia guardados en el archivo con la cola de encolados
    cargar_cola(&entregados,nombre_archivo);//Enlazo los datos que tenia guardados en el archivo de entregados con la cola de entregados
    printf("\n");
    system("pause");
    system("cls");

    Nodo *temp_encolados=micola.frente;  //Con este puntero que pasa por todos los nodos de la cola de encolados
                                         //voy a contar las concesionarias y los pedidos que hay en encolados
    while(temp_encolados!=NULL)
    {
        contador_encolados++;
        if(temp_encolados->p.con.ID_concesionaria>contador_concesionarias)
        {
            contador_concesionarias=temp_encolados->p.con.ID_concesionaria;
        }
        temp_encolados=temp_encolados->siguiente;
    }

    Nodo *temp_entregados=entregados.frente; //Con este otro hago lo mismo pero en la cola de entregados
    while(temp_entregados!=NULL)
    {
        contador_entregados++;
        if(temp_entregados->p.con.ID_concesionaria>contador_concesionarias)
        {
            contador_concesionarias=temp_entregados->p.con.ID_concesionaria;
        }
        temp_entregados=temp_entregados->siguiente;
    }

    id_concesionaria=contador_concesionarias; //Una vez calculado cuantos pedidos y encolados tenia actualizo la variable
    id_pedido+=(contador_encolados +contador_entregados);

    printf("Bienvenido al programa de pedidos y entrergas de la empresa!\n");
    printf("A continuacion el menu de opciones\n");

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
        printf("6) Reporte concesionarias\n");
        printf("7) Salir del programa\n");
        printf("Opcion: ");
        scanf("%d", &opc);
        system("cls");

        switch (opc) {
        case 1: {
            Pedidos p = ingresar_pedido(micola,entregados); //Se encolan los pedidos
            encolar(&micola, p);
            printf("\nPedido encolado con exito! ");
        } break;
        case 2:
            if (!colaVacia(micola)) {

                strcpy(micola.frente->p.estado,"entregado"); //Le cambio el estado al desencolar
                encolar(&entregados, micola.frente->p); //Lo encolo en la lista de los pedios entregados y le pasas nada mas que los datos del pedido
                desencolar(&micola);                    //y despues lo desencolo de la lista de encolados
                printf("Pedido desencolado con exito");
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
            buscar_pedido(micola,entregados);
            break;
        case 6:
            concesionarias(micola,entregados);
            break;
        case 7:
            guardar_cola(&micola, nombre_encolados); //Al salir del programa guardamos los datos las dos listas enlazadas
            guardar_cola(&entregados, nombre_archivo);//en los archivos binarios
            liberar_cola(&micola);//Liberamos todos los nodos de las dos colas
            liberar_cola(&entregados);
            printf("Hasta la proxima!\n");
            printf("Saliendo del programa...\n");
            break;
        default:
            printf("Numero fuera de rango.\n");
        }
    } while (opc != 7);

    return 0;
}

void inicializar_cola(Cola *cola) { //Inicializamos la cola
    cola->frente = NULL;
    cola->final = NULL;
}

void encolar(Cola *cola, Pedidos x) {
    Nodo *nuevo = malloc(sizeof(Nodo)); //Guardamos el nodo en la memoria dinamica
    nuevo->p = x; //Asignamos una variable al struct de pedidos
    nuevo->siguiente = NULL; //Apuntamos el siguiente nodo a NULL

    if (colaVacia(*cola)) { //Si la cola esta vacia hacemos que el frente de la cola apunte a el nuevo primer nodo
        cola->frente = nuevo;//y al nodo final
        cola->final = nuevo;
    } else {
        cola->final->siguiente = nuevo; //Si no esta vacia ponemos al nodo nuevo ultimo en la cola
        cola->final = nuevo;
    }
}

int colaVacia(Cola cola) {
    return cola.frente == NULL; //Si la cola esta vacia devulve TRUE
}

void desencolar(Cola *cola) {
    if (colaVacia(*cola)) {
        printf("\nLa cola esta vacia.\n");
        return;
    }

    Nodo *temp = cola->frente;  //Agarra el primer nodo de la cola que le pasaste y lo elimina
    cola->frente = cola->frente->siguiente;

    if (cola->frente == NULL) { //Si no hay segundo nodo a donde apuntar la cola esta vacia
        cola->final = NULL;     //asi que asignamos tambien a cola final como NULL
    }

    free(temp); //Liberamos el nodo
}

Pedidos ingresar_pedido(Cola cola,Cola cola_entregados) {
    Pedidos x;

    id_pedido++; //Sumas un pedido a la variable global
    x.ID_pedidos = id_pedido; //Lo igualas al ID del pedido

    printf("Datos de la concesionaria: ");
    printf("\n\tNombre de la concesionaria: ");
    fflush(stdin);
    scanf(" %[^\n]",x.con.nombre_concesionaria);
    printf("\tDireccion: ");
    fflush(stdin);
    scanf(" %[^\n]",x.con.direccion);
    printf("\tNombre del gerente: ");
    fflush(stdin);
    scanf(" %[^\n]",x.con.gerente);

    int encontrado = 0; //Flag de programacion
    Nodo *temp = cola.frente;
    while (temp != NULL && !encontrado) { //Busco en la cola de los encolados si el nombre de la concesionaria exite para asi asignarle el mismo ID de concesionaria
        if (strcmp(temp->p.con.nombre_concesionaria, x.con.nombre_concesionaria) == 0) {
            x.con.ID_concesionaria = temp->p.con.ID_concesionaria;
            encontrado = 1;
        }
        temp = temp->siguiente;
    }

    if(!encontrado) //Si no encontro en los encolados me fijo en la cola de los entregados
    {
        Nodo *temp_entregados = cola_entregados.frente;
        while (temp_entregados != NULL && !encontrado) {
            if (strcmp(temp_entregados->p.con.nombre_concesionaria, x.con.nombre_concesionaria) == 0) {
                x.con.ID_concesionaria = temp_entregados->p.con.ID_concesionaria;
                encontrado = 1;
            }
            temp_entregados = temp_entregados->siguiente;
        }
    }

    if (!encontrado) { //Si no esta en ninguna de las dos colas significa que es una concesionaria nueva por lo que le doy un nuevo ID
        id_concesionaria++;
        x.con.ID_concesionaria = id_concesionaria;
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
        printf("\tID concesionaria: %d\n", temp->p.con.ID_concesionaria);
        printf("\tConcesionaria: %s\n", temp->p.con.nombre_concesionaria);
        printf("\tDireccion: %s\n", temp->p.con.direccion);
        printf("\tGerente: %s\n", temp->p.con.gerente);
        printf("\n-----------------------\n");
        temp = temp->siguiente;
    }
}

void liberar_cola(Cola *cola) { //Liberacion de los nodos
    while (!colaVacia(*cola)) {
        desencolar(cola);
    }
}

void guardar_cola(Cola *cola, char *nombre_archivo) {
    FILE *archivo = fopen(nombre_archivo, "wb"); //Cada vez que salgo del programa se sobreescriben los datos
    if (archivo==NULL) {
        printf("\nError al abrir archivo para guardar cola");
        return;
    }

    Nodo *temp = cola->frente;
    while (temp != NULL) {
        fwrite(&(temp->p), sizeof(Pedidos), 1, archivo); //Escribo todo lo que hay en la cola que le pase a la funcion en el archivo
        temp = temp->siguiente;
    }
    fclose(archivo);
}

void cargar_cola(Cola *cola, char *nombre_archivo) {
    FILE *archivo = fopen(nombre_archivo, "rb"); //Leo los datos del archivo que le paso por funcion
    if (archivo==NULL) {
        printf("Archivo %s no encontrado. Iniciando cola vacia.\n", nombre_archivo);
        return;
    }

    Pedidos pedido;
    while (fread(&pedido, sizeof(Pedidos), 1, archivo)) { //Cada pedido que lea lo va a encolar
        encolar(cola, pedido);
    }
    fclose(archivo);
}

void buscar_pedido(Cola cola_encolados,Cola cola_entregados)
{
    if((colaVacia(cola_encolados) && colaVacia(cola_entregados)))
    {
        printf("\nNo hay pedidos ni encolados ni entregados");
        return;
    }
    int opc;
    printf("Ingrese el ID del pedido a buscar: ");
    scanf("%d",&opc);

    Pedidos pedido;
    int encontrado=0;

    Nodo* temp_encolados;
    temp_encolados=cola_encolados.frente;
                                            //Voy a buscar el ID en las dos colas
    Nodo * temp_entregados;
    temp_entregados=cola_entregados.frente;


    while((temp_encolados!=NULL) && (!encontrado)) //Primero busco en los encolados
    {
        if(temp_encolados->p.ID_pedidos==opc)
        {
            printf("El pedido con ID %d esta encolado",opc);
            printf("\n\nDatos del pedido:\n");
            printf("\tID del pedido: %d\n", temp_encolados->p.ID_pedidos);
            printf("\tMarca: %s\n", temp_encolados->p.marca);
            printf("\tModelo: %s\n", temp_encolados->p.modelo);
            printf("\tPrecio: %.2f\n", temp_encolados->p.precio);
            printf("\tEstado: %s\n", temp_encolados->p.estado);
            printf("\tID concesionaria: %d\n", temp_encolados->p.con.ID_concesionaria);
            printf("\tConcesionaria: %s\n", temp_encolados->p.con.nombre_concesionaria);
            printf("\tDireccion: %s\n", temp_encolados->p.con.direccion);
            printf("\tGerente: %s\n", temp_encolados->p.con.gerente);
            encontrado=1;
        }
        else
        {
            temp_encolados=temp_encolados->siguiente;
        }
    }

    if(!encontrado) //Si no esta busco en la cola de los entregados
    {
        while((temp_entregados!=NULL) && (!encontrado))
        {
            if(temp_entregados->p.ID_pedidos==opc)
            {
                printf("El pedido %d fue entregado",opc);
                printf("\n\nDatos del pedido:\n");
                printf("\tID del pedido: %d\n", temp_entregados->p.ID_pedidos);
                printf("\tMarca: %s\n", temp_entregados->p.marca);
                printf("\tModelo: %s\n", temp_entregados->p.modelo);
                printf("\tPrecio: %.2f\n", temp_entregados->p.precio);
                printf("\tEstado: %s\n", temp_entregados->p.estado);
                printf("\tID concesionaria: %d\n", temp_entregados->p.con.ID_concesionaria);
                printf("\tConcesionaria: %s\n", temp_entregados->p.con.nombre_concesionaria);
                printf("\tDireccion: %s\n", temp_entregados->p.con.direccion);
                printf("\tGerente: %s\n", temp_entregados->p.con.gerente);
                encontrado=1;

            }
            else
            {
                temp_entregados=temp_entregados->siguiente;
            }
        }
    }

    if(!encontrado) //Si no esta en ninguna de las dos el ID no existe
    {
        printf("\nNo existe ningun pedido con ese ID");
    }
}

void concesionarias(Cola cola_encolados, Cola cola_entregados) {

    Nodo *temp_encolados = cola_encolados.frente;   //Voy a utilizar las dos colas
    Nodo *temp_entregados = cola_entregados.frente;

    FILE *archivo_txt=NULL;
    char *nombre_archivo="datos_concesionarias.txt";  //Voy a guardar los datos en un archivo de texto

    archivo_txt=fopen(nombre_archivo,"w"); //Lo sobreescribo siempre
    if(archivo_txt==NULL)
    {
        printf("Error al abir el archivo de texto para guardar los datos");
        return;
    }

    char nombre_concesionaria_mas_ventas[50] = "";
    char nombre_concesionaria_mas_recaudado[50] = "";

    float ventas = 0;
    int pedidos = 0;

    int ids_procesados_encolados[100];
    int cantidad_ids_encolados = 0;

    printf("Pedidos y recaudaciones por concesionaria (Encargos en espera):\n\n");
    fprintf(archivo_txt,"Pedidos y recaudaciones por concesionaria (Encargos en espera):\n");

    if(colaVacia(cola_encolados))
    {
        printf("\nNo hay pedidos encolados");
    }

    while (temp_encolados != NULL) { //Voy a ir pasando por cada nombre de la consecionaria de cada nodo
        int ya_encontrado = 0;

        // Compruebo si ya fue encontrado el ID
        for (int i = 0; i < cantidad_ids_encolados; i++) {
            if (temp_encolados->p.con.ID_concesionaria == ids_procesados_encolados[i]) {
                ya_encontrado = 1;
                break;
            }
        }

        if (!ya_encontrado) { //Si no fue encontrado busco toda la informacion de esa consecionaria primero en los encolados
            float ventas_por_concesionaria = 0; //Guardo cuantas ventas y pedidos tuvo esta consecionaria
            int pedidos_por_concesionaria = 0;

            Nodo *aux_encolados = cola_encolados.frente;
            while (aux_encolados != NULL) {
                if (aux_encolados->p.con.ID_concesionaria == temp_encolados->p.con.ID_concesionaria) {
                    ventas_por_concesionaria += aux_encolados->p.precio;
                    pedidos_por_concesionaria++;
                }
                aux_encolados = aux_encolados->siguiente; //Voy comparando cada nombre de concecionaria con cada nodo
            }

            printf("Concesionaria: %s | Pedidos: %d | Recaudacion: %.2f\n",temp_encolados->p.con.nombre_concesionaria, pedidos_por_concesionaria, ventas_por_concesionaria);
            printf("-----------------------------------------------------------");
            fprintf(archivo_txt,"Concesionaria: %s | Pedidos: %d | Recaudacion: %.2f\n",temp_encolados->p.con.nombre_concesionaria, pedidos_por_concesionaria, ventas_por_concesionaria);

            if (ventas_por_concesionaria > ventas) { //Va chquiando cual consecionaria vendio mas
                ventas = ventas_por_concesionaria;
                strcpy(nombre_concesionaria_mas_recaudado, temp_encolados->p.con.nombre_concesionaria);
            }

            if (pedidos_por_concesionaria > pedidos) { //Va chequiando cual consecionaria tuvo mas pedidos
                pedidos = pedidos_por_concesionaria;
                strcpy(nombre_concesionaria_mas_ventas, temp_encolados->p.con.nombre_concesionaria);
            }

            ids_procesados_encolados[cantidad_ids_encolados] = temp_encolados->p.con.ID_concesionaria; //Guarda el ID de la consecionaria en los IDs ya encontrados para que despues no se vuelva a contabilizar
            cantidad_ids_encolados++;
        }

        temp_encolados = temp_encolados->siguiente; //Paso al siguiente nodo
    }

    printf("\n\n\nPedidos y recaudaciones por concesionaria (Entregas realizadas):\n");
    fprintf(archivo_txt,"\nPedidos y recaudaciones por concesionaria (Entregas realizadas):\n");

    if(colaVacia(cola_entregados))
    {
        printf("\nNo hay pedidos entregados");
        return;
    }

    // Reiniciar variables para la cola de entregados
    int ids_procesados_entregados[100];
    int cantidad_ids_entregados = 0;


    while (temp_entregados != NULL) { //Hago lo mismo pero ahora con la lista de los entregados
        int ya_encontrado = 0;



        for (int i = 0; i < cantidad_ids_entregados; i++) {
            if (ids_procesados_entregados[i] == temp_entregados->p.con.ID_concesionaria) {
                ya_encontrado = 1;
                break;
            }
        }

        if (!ya_encontrado) {
            float ventas_por_concesionaria = 0;
            int pedidos_por_concesionaria = 0;

            Nodo *aux_entregados = cola_entregados.frente;
            while (aux_entregados != NULL) {
                if (aux_entregados->p.con.ID_concesionaria == temp_entregados->p.con.ID_concesionaria) {
                    ventas_por_concesionaria += aux_entregados->p.precio;
                    pedidos_por_concesionaria++;
                }
                aux_entregados = aux_entregados->siguiente;
            }

            printf("\nConcesionaria: %s | Pedidos: %d | Recaudacion: %.2f",
                   temp_entregados->p.con.nombre_concesionaria, pedidos_por_concesionaria, ventas_por_concesionaria);
            printf("\n-----------------------------------------------------------");
            fprintf(archivo_txt,"Concesionaria: %s | Pedidos: %d | Recaudacion: %.2f\n",
                   temp_entregados->p.con.nombre_concesionaria, pedidos_por_concesionaria, ventas_por_concesionaria);

            if (ventas_por_concesionaria > ventas) {
                ventas = ventas_por_concesionaria;
                strcpy(nombre_concesionaria_mas_recaudado, temp_entregados->p.con.nombre_concesionaria);
            }

            if (pedidos_por_concesionaria > pedidos) {
                pedidos = pedidos_por_concesionaria;
                strcpy(nombre_concesionaria_mas_ventas, temp_entregados->p.con.nombre_concesionaria);
            }

            ids_procesados_entregados[cantidad_ids_entregados] = temp_entregados->p.con.ID_concesionaria;
            cantidad_ids_entregados++;
        }

        temp_entregados = temp_entregados->siguiente;
    }

    printf("\n\nConcesionaria con mas ventas: %s (%d pedidos)\n", nombre_concesionaria_mas_ventas, pedidos);
    printf("Concesionaria con mas recaudacion: %s (%.2f en ventas)\n", nombre_concesionaria_mas_recaudado, ventas);
    fprintf(archivo_txt,"\nConcesionaria con mas ventas: %s (%d pedidos)\n", nombre_concesionaria_mas_ventas, pedidos);
    fprintf(archivo_txt,"Concesionaria con mas recaudacion: %s (%.2f en ventas)\n", nombre_concesionaria_mas_recaudado, ventas);


    fclose(archivo_txt);
}