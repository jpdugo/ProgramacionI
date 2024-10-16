/*

modificar el programa para que:

1) Utilice mem dinamica
2) pase parametros en las funciones (Arhivos, valores.....)
3) mejore la estetica
4) mejore todo lo posible....




*/





#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct datos_coches
{
   char marca[20];
   char modelo[20];
   char dominio[10];
   float precio;

}autos;

void agregar();
void listar();
void buscar ();
void vaciar();
void salir();


int main()
{
    int opcion=0;
    printf("\n\nMENU DE OPCIONES:");
    printf("\n*******************\n");
    printf("\n 1) AGREGAR AUTOS");
    printf("\n 2) LISTAR AUTOS");
    printf("\n 3) BUSCAR AUTOS");
    printf("\n 4) VACIAR ARCHIVO");
    printf("\n 5) SALIR DEL PROGRAMA");

    printf("\n\nIngrese la opcion deseada: ");
    scanf("%d", &opcion);

    switch(opcion)
    {
        case 1: agregar();
                break;

        case 2: listar();
                break;

        case 3: buscar();
                break;

        case 4: vaciar();
                break;

        case 5: salir();
                break;

        default: printf("\nLa opcion no es valida...");

    }
    system("pause");

    return 0;
}

void agregar()
{
    int i, cant_autos=0;
    FILE * fp=NULL;
    char *archivo="autos.bin";

    fp=fopen(archivo, "ab");

        if (fp==NULL)
        {
            printf("\nError al abrir el archivo.");
            exit(1);
        }
    else
    {
        printf("El archivo se abrio correctamente...\n");
    }

    printf("\nCUantos autos desea ingresar?: ");
    scanf("%d", &cant_autos);

    for (i=0; i<cant_autos; i++)
    {
        printf("\nIngrese la Marca: ");
        fflush(stdin);
        gets(autos.marca);

        printf("\nIngrese el Modelo: ");
        fflush(stdin);
        gets(autos.modelo);

        printf("\nIngrese el Dominio: ");
        fflush(stdin);
        gets(autos.dominio);

        printf("\nIngrese el Precio: ");
        scanf("%f", &autos.precio);

        fwrite(&autos, sizeof(autos), 1, fp);
        fputc('\n', fp);

    }

    fclose(fp);
    main();

}

void listar()
{
    int cant_registros=0, i=0;
    FILE *fp=NULL;
    char *archivo="autos.bin";

    fp=fopen(archivo, "rb");

        if (fp==NULL)
        {
            printf("\nError al abrir el archivo.");
            exit(1);
        }
    else
    {
        printf("El archivo se abrio correctamente...\n");
    }

    fseek(fp, 0, SEEK_END);

    cant_registros=ftell(fp)/(sizeof(autos)+1);

    printf("\n\nLa cantidad de registros que tiene autos.bin es: %d", cant_registros);

    rewind(fp);

    fread(&autos, sizeof(autos), 1, fp);
    while(!feof(fp))
    {
        i=i+1;
        printf("\nRegistro Nro: %d", i);
        printf("\nLa Marca es: ");
        puts(autos.marca);
        printf("\nEl modelo es: ");
        puts(autos.modelo);
        printf("\nEl Dominio es: ");
        puts(autos.dominio);
        printf("\nEl Precio es: %f", autos.precio);
        printf("\n\n");
        fgetc(fp);

        fread(&autos, sizeof(autos), 1, fp);
        system("pause");

    }
    printf("\n\tLECTURA FINALIZADA...");
    system("pause");
    fclose(fp);
    main();

}

void buscar()
{
    char busqueda[50];
    //char aux;
    int flag;

    FILE *fp=NULL;
    char *archivo="autos.bin";

    fp=fopen(archivo, "rb");

        if (fp==NULL)
        {
            printf("\nError al abrir el archivo.");
           exit(1);
        }
    else
    {
        printf("El archivo se abrio correctamente...\n");
    }

    printf("\nIngrese marca o modelo a buscar: ");
    fflush(stdin);
    gets(busqueda);
    printf("\n\nVamos a buscar la palabra: %s", busqueda);

    fread(&autos, sizeof(autos), 1, fp);
    while (!feof(fp))
    {
        if (((strstr(autos.marca, busqueda))) || ((strstr(autos.modelo, busqueda))))
        {
            flag=1;
            printf("\nSE HAN ENCONTRADO LOS SIGUIENTES RESULTADOS:\n");
            printf("\nLa Marca es: ");
            puts(autos.marca);

            printf("\nEl modelo es: ");
            puts(autos.modelo);

            printf("\nEl dominio es: ");
            puts(autos.dominio);

            printf("\nEl precio es: %f", autos.precio);

            system("pause");

        }
        fgetc(fp);
        fread(&autos, sizeof(autos), 1, fp);
    }

    if (flag==0)
    {
        printf("\n\tNO HAY COINCIDENCIAS EN EL ARCHIVO...\n\n");
    }
    fclose(fp);
    main();
}


void vaciar()
{
    int a;
    FILE * fp=NULL;
    char *archivo="autos.bin";

    fp=fopen(archivo, "w+");

        if (fp==NULL)
        {
            printf("\nError al abrir el archivo.");
            exit(1);
        }
    else
    {
        printf("El archivo se abrio correctamente...\n");
    }

    a=fflush(fp);

    if (a==0)
    {
        system("cls");
        printf("\nArchivo Vaciado...");
    }
    else
    {
         printf("\nError al vaciar el archivo...");
    }
    main();
}

void salir()
{
    system("cls");
    printf("FIN DEL PROGRAMA...");
    exit(1);
}
