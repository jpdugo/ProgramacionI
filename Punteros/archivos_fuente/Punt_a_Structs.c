#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char nombre[30];
    char apellido[20];
    char telefono[15];
    int edad;
} Dato_Amigo;

void adquirir_datos(Dato_Amigo *p);
void imprimir_datos(Dato_Amigo *p);

int main()

{
    Dato_Amigo V1[2];
    Dato_Amigo *p = NULL;

    p = V1;

    adquirir_datos(p);

    imprimir_datos(p);

    return 0;
}

void adquirir_datos(Dato_Amigo *p)
{
    for (int i = 0; i < 2; i++)
    {
        printf("\n\n\nIngresa nombre de tu amigo: ");
        fflush(stdin);
        gets((p + i)->nombre);
        printf("\nIngresa apellido de tu amigo: ");
        fflush(stdin);
        gets((p + i)->apellido);
        printf("\nIngresa telefono de tu amigo: ");
        fflush(stdin);
        gets((p + i)->telefono);
        printf("\nIngresa la edad de tu amigo: ");
        fflush(stdin);
        scanf("%d", &(p + i)->edad);
    }
}

void imprimir_datos(Dato_Amigo *p)
{
    for (int i = 0; i < 2; i++)
    {
        printf("\n\n\n\tTu amigo se llama: %s %s\n", (p + i)->nombre, (p + i)->apellido);
        printf("\n\tSu telefono es: %s\n", (p + i)->telefono);
        printf("\n\tSu edad es: %d\n", (p + i)->edad);
    }
}
