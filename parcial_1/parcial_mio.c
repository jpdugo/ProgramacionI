// Juan Patricio Dugo

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct
{
    char Producto_tipo[20]; //reactivo, solvente o mezcla
    char Codigo_producto[20]; // xx123AB
    int Cantidad_vendida; // rand entre 1 y 500
    char Estado[10]; // normal/agotado
} Producto;

//prototipo de funciones

// Pedidas por el examen
void Registrar(Producto * buffer, char * nombreArchivo, FILE * archivo, char * nombreArchivoLog, FILE * archivoLog);
void Listar(Producto * buffer, char * nombreArchivo, FILE * archivo);
void Listar_Agotados(Producto * buffer, char * nombreArchivo, FILE * archivo);
void Buscar_Producto(Producto * buffer, char * nombreArchivo, FILE * archivo);
void Editar_producto(Producto * buffer, char * nombreArchivo, FILE * archivo);
void Salir(int valorSalida,Producto * buffer);



// helpers mios
char * Get_horario() {

 char * hora = (char *) malloc(sizeof(char) * 10);
 if (hora == NULL) {
    printf("No se pudo asignar memoria");
    exit(1);
 }
 time_t t;
 struct tm *timeinfo;
 time(&t);
 timeinfo = localtime(&t);

 sprintf(hora, "%02d:%02d:%02d", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);

 return hora;
}

// Voy a reutilizar esto por todos lados
void Imprimir_buffer(Producto * buffer)
{
    printf("Producto Tipo: %s\n", buffer->Producto_tipo);
    printf("Codigo: %s\n", buffer->Codigo_producto);
    printf("Cantidad Vendida: %d\n", buffer->Cantidad_vendida);
    printf("Estado %s\n", buffer->Estado);
}

int main()
{
    char * nombreArchivo = "productos.bin";
    char * nombreArchivoLog = "agotados.txt";
    FILE * archivo = NULL;
    FILE * archivoLog = NULL;
    Producto * buffer = (Producto *) malloc(sizeof(Producto));
    int opcion;

    do
    {
        system("cls");
        printf("Ingrese una de las siguientes opciones:\n");
        printf("1. Registrar Producto:\n");
        printf("2. Listar Productos:\n");
        printf("3. Listar Productos Agotados:\n");
        printf("4. Buscar Productos:\n");
        printf("5. Editar Productos:\n");
        printf("6. Salir:\n");

        fflush(stdin);
        scanf("%d", &opcion);

        switch (opcion)
        {
            case 1:
                system("cls");
                Registrar(buffer, nombreArchivo, archivo, nombreArchivoLog, archivoLog);
                break;
            case 2:
                system("cls");
                Listar(buffer, nombreArchivo, archivo);
                break;
            case 3:
                system("cls");
                Listar_Agotados(buffer, nombreArchivo, archivo);
                break;
            case 4:
                system("cls");
                Buscar_Producto(buffer, nombreArchivo, archivo);
                break;
            case 5:
                Editar_producto(buffer, nombreArchivo, archivo);
                break;
            case 6:
                Salir(0, buffer);
                break;
        }
    } while (opcion != 6);

    return 0;
}

void Registrar(Producto * buffer, char * nombreArchivo, FILE * archivo, char * nombreArchivoLog, FILE * archivoLog)
{
    archivo = fopen(nombreArchivo, "ab");
    if (archivo == NULL)
    {
        printf("fallo al abrir el archivo");
        exit(-1);
    }


    // popular buffer
    printf("Ingrese el tipo de producto\n");
    printf("1. reactivo\n");
    printf("2. solvente\n");
    printf("3. mezcla\n");
    int tipo;
    fflush(stdin);
    scanf("%d", &tipo);

    switch(tipo)
    {
       case 1:
            strcpy(buffer->Producto_tipo, "reactivo");
       case 2:
            strcpy(buffer->Producto_tipo, "solvente");
       case 3:
            strcpy(buffer->Producto_tipo, "mezcla");
    }

    printf("Ingrese el codigo del producto\n");
    fflush(stdin);
    gets(buffer->Codigo_producto);

    // simulacion
    srand(time(NULL));
    buffer->Cantidad_vendida = 1 + rand() % 500;

    char * horario = Get_horario();

    if (buffer->Cantidad_vendida > 400)
    {
        strcpy(buffer->Estado, "agotado");
        archivoLog = fopen(nombreArchivoLog, "a");
        fprintf(archivoLog, "\n%s: Se registra agotamiento:\n\n", horario);
        fprintf(archivoLog, "Producto Tipo: %s\n", buffer->Producto_tipo);
        fprintf(archivoLog, "Codigo: %s\n", buffer->Codigo_producto);
        fprintf(archivoLog, "Cantidad Vendida: %d\n", buffer->Cantidad_vendida);
        fprintf(archivoLog, "Estado %s\n", buffer->Estado);
        fclose(archivoLog);
    } else
    {
        strcpy(buffer->Estado, "normal");
    }

    fwrite(buffer, sizeof(Producto), 1, archivo);
    fclose(archivo);
    archivo = NULL;
    free(horario);

}

void Listar(Producto * buffer, char * nombreArchivo, FILE * archivo)
{
    archivo = fopen(nombreArchivo, "rb");
    if (archivo == NULL)
    {
        printf("No se pudo asignar memoria o no hay archivos registrados, verifique:\n");
        exit(1);
    }

    printf("Los productos listados son los siguientes:\n");

    while(fread(buffer, sizeof(Producto), 1, archivo)) {
        Imprimir_buffer(buffer);
        printf("-----\n");
    }

    fclose(archivo);
    archivo = NULL;

    system("PAUSE");
}

void Listar_Agotados(Producto * buffer, char * nombreArchivo, FILE * archivo)
{
    int flag = 0;
    archivo = fopen(nombreArchivo, "rb");
    if (archivo == NULL)
    {
        printf("No se pudo asignar memoria o no hay productos registrados:\n");
        exit(1);
    }

    printf("Los productos agotados son los siguientes:\n");

    while(fread(buffer, sizeof(Producto), 1, archivo)) {
    if (buffer->Cantidad_vendida > 400)
    {
        flag = 1;
        Imprimir_buffer(buffer);
        printf("-----\n");
    }
    }

    if (flag == 0)
    {
        printf("no se han registrado productos agotados:");
    }

    fclose(archivo);
    archivo = NULL;

    system("PAUSE");
}

void Buscar_Producto(Producto * buffer, char * nombreArchivo, FILE * archivo)
{
    int flag = 0;
    char busqueda[20];
    archivo = fopen(nombreArchivo, "rb");
    if (archivo == NULL)
    {
        printf("no se pudo asignar memoria o no hay productos registrados, verifique:\n");
        exit(1);
    }

    printf("Ingrese el codigo a buscar:\n");
    fflush(stdin);
    scanf("%s", busqueda);


    while(fread(buffer, sizeof(Producto), 1, archivo) && flag == 0) {
        if (strcasecmp(busqueda, buffer->Codigo_producto) == 0)
        {
            flag = 1;
            printf("\n\nSe ha encontrado un match!:\n");
            Imprimir_buffer(buffer);
            printf("-----\n");
        }
    }

    if (flag == 0)
    {
        printf("Lo siento, no se han encontrado coincidencias\n");
    }

    fclose(archivo);
    archivo = NULL;

    system("PAUSE");
}

void Editar_producto(Producto * buffer, char * nombreArchivo, FILE * archivo)
{

    int flag = 0;
    char busqueda[20];
    long contadorProductos = 0;
    archivo = fopen(nombreArchivo, "r+b");
    if (archivo == NULL)
    {
        printf("no se pudo asignar memoria o no hay productos registrados, verifique:\n");
        exit(1);
    }

    printf("Ingrese el codigo a buscar:\n");
    fflush(stdin);
    scanf("%s", busqueda);


    fseek(archivo, 0, SEEK_SET);
    while(fread(buffer, sizeof(Producto), 1, archivo) && flag == 0) {
        contadorProductos++;
        if (strcasecmp(busqueda, buffer->Codigo_producto) == 0)
        {
            flag = 1;
            printf("\n\nSe ha encontrado un match!:\n");
            Imprimir_buffer(buffer);
            printf("-----\n");
        }
    }

    if (flag == 1)
    {

        printf("Edite la informacion del producto por favor...\n\n");

        printf("Ingrese el tipo de producto\n");
        printf("1. reactivo\n");
        printf("2. solvente\n");
        printf("3. mezcla\n");
        int tipo;
        fflush(stdin);
        scanf("%d", &tipo);

        switch(tipo)
        {
           case 1:
                strcpy(buffer->Producto_tipo, "reactivo");
           case 2:
                strcpy(buffer->Producto_tipo, "solvente");
           case 3:
                strcpy(buffer->Producto_tipo, "mezcla");
        }

        printf("Ingrese el codigo del producto\n");
        fflush(stdin);
        gets(buffer->Codigo_producto);

        printf("Ingrese un entero con la cantidad vendida: \n");
        fflush(stdin);
        scanf("%d", &buffer->Cantidad_vendida);

        printf("Ingrese el estado del producto, puede ser normal o agotado: \n");
        fflush(stdin);
        gets(buffer->Estado);

        // edito el archivo binario
        fseek(archivo, sizeof(Producto) * (contadorProductos - 1), SEEK_SET);
        fwrite(buffer, sizeof(Producto), 1, archivo);

        printf("Los datos fueron cargados correctamente:\n");
    } else
    {
        printf("Lo siento, no se han encontrado coincidencias\n");
    }

    fclose(archivo);
    archivo = NULL;
    system("PAUSE");

}

void Salir(int valorSalida,Producto * buffer)
{
    system("cls");
    printf("Se ha cerrado la aplicacion, hasta Luego!\n");
    free(buffer);
    exit(valorSalida);
}
