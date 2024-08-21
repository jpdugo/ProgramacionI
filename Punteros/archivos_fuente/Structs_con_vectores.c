#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char nombre[30];
    char apellido[20];
    char telefono[15];
    int edad;
} Dato_Amigo;

void adquirir_datos(Dato_Amigo V1[]);
void imprimir_datos(Dato_Amigo V1[]);

int main()

{
    Dato_Amigo V1[2];

    adquirir_datos(V1);
    imprimir_datos(V1);

    return 0;
}

void adquirir_datos(Dato_Amigo V1[])
{
    for (int i = 0; i < 2; i++)
    {
        printf("\n\n\nIngresa nombre de tu amigo: ");
        fflush(stdin);
        gets(V1[i].nombre);
        printf("\nIngresa apellido de tu amigo: ");
        fflush(stdin);
        gets(V1[i].apellido);
        printf("\nIngresa telefono de tu amigo: ");
        fflush(stdin);
        gets(V1[i].telefono);
        printf("\nIngresa la edad de tu amigo: ");
        fflush(stdin);
        scanf("%d", &V1[i].edad);
    }
}

void imprimir_datos(Dato_Amigo V1[])
{
    for (int i = 0; i < 2; i++)
    {
        printf("\n\n\n\tTu amigo se llama: %s %s\n", V1[i].nombre, V1[i].apellido);
        printf("\n\tSu telefono es: %s\n", V1[i].telefono);
        printf("\n\tSu edad es: %d\n", V1[i].edad);
    }
}
