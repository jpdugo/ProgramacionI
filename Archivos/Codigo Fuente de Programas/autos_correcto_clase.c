#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char marca[50];
    char modelo[50];
    char dominio[50];
    float precio;
}autos;

void agregarAutos(autos *aut, FILE *fp);
void listarAutos(autos *aut, FILE *fp);
void buscar(autos *aut, FILE *fp);
void borrar(FILE *fp);

int main()
{
    FILE *fp=NULL;
    int op;
    autos *puntero = NULL;

    puntero=(autos *) malloc(sizeof(autos));



    do{
        printf("Elegi: \n1) A�adir nuevos autos al final \n2) Listar todos los registros \n3) Buscar x marca o modelo \n4) Vaciar archivo \n5) Salir\n");
        fflush(stdin);
        scanf("%d",&op);
        switch(op)
        {
        case 1:
            system("cls");
            agregarAutos( puntero, fp);
            system("cls");
            break;
        case 2:
            listarAutos(puntero, fp);
            break;
        case 3:
            buscar(puntero, fp);
            break;
        case 4:
            borrar(fp);
            break;
        case 5:
            system("cls");
            printf("chau");
            break;
        }
        //system("cls");
    }while(op!=5);
    return 0;
}

void agregarAutos(autos *aut, FILE *fp){
    fp=fopen("autos.bin","ab");
    printf("Ingrese marca: ");
    fflush(stdin);
    gets(aut->marca);

    printf("Ingrese modelo: ");
    fflush(stdin);
    gets(aut->modelo);

    printf("Ingrese dominio: ");
    fflush(stdin);
    gets(aut->dominio);

    printf("Ingrese precio: ");
    fflush(stdin);
    scanf("%f",&aut->precio);

    fwrite(aut,sizeof(autos),1,fp);
    fputc('\n',fp);
    //free(aut);
    fclose(fp);
}

void listarAutos(autos *aut, FILE *fp){
    system("cls");
    fp=fopen("autos.bin","rb");
    //rewind(fp);
    fseek(fp,0,SEEK_END);
    if(fp==NULL){
        printf("ERROR");
        return -1;
    }
    int cant_registros=0;
    cant_registros=ftell(fp)/(sizeof(autos)+1);
    printf("Cantidad de registros: %d",cant_registros);
    rewind(fp);
    fread(aut, sizeof(autos),1,fp);
    //printf("%s",texto);
    while(!feof(fp)){
        printf("\nMarca: %s - Modelo: %s - Dominio: %s - Precio: %f",aut->marca, aut->modelo, aut->dominio, aut->precio);
        fgetc(fp);
        fread(aut, sizeof(autos),1,fp);
    }
    fclose(fp);
    printf("\n");
    system("pause");
    system("cls");
}

void buscar(autos *aut, FILE *fp){
    system("cls");
    fp=fopen("autos.bin","rb");
    //rewind(fp);
    char modelo[50];
    printf("Ingrese modelo a buscar: ");
    fflush(stdin);
    gets(modelo);
    rewind(fp);
    fread(aut, sizeof(autos),1,fp);
    //printf("%s",texto);
    while(!feof(fp)){
        if(strstr(modelo,aut->modelo)){
            printf("\nMarca: %s - Modelo: %s - Dominio: %s - Precio: %f",aut->marca, aut->modelo, aut->dominio, aut->precio);
        }
        fgetc(fp);
        fread(aut, sizeof(autos),1,fp);
    }
    fclose(fp);
    printf("\n");
    system("pause");
    system("cls");
}

void borrar(FILE *fp){
    fp=fopen("autos.bin","w");
    fclose(fp);
    system("cls");
}
