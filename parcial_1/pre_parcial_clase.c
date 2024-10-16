#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


typedef struct
{
    char vehiculo_tipo[20];
    int velocidad_registrada;
    char patente[20];
    char estado[20];

}Vehiculo;

void registar(FILE *archivo,Vehiculo *v,char *nombre);
void listar_vehiculos(FILE *archivo,Vehiculo *v,char *nombre);
void listar_multados(FILE *archivo,Vehiculo *v,char *nombre);
void buscar_vehiculo(FILE *archivo,Vehiculo *v,char *nombre);
void editar_vehiculo(FILE *archivo,Vehiculo *v,char *nombre);
void borrar_archivo(FILE *archivo,char *nombre,char *nombre_txt,FILE *archivo_txt);

int cant_vehiculos=0;
int main()
{
    Vehiculo *v=NULL;
    v=malloc(sizeof(Vehiculo)*1);
    if(v==NULL){printf("error al asignar memoria");return -1;}

    FILE *archivo_texto=NULL;
    char *nombre_archivo_txt="Log.txt";
    archivo_texto=fopen(nombre_archivo_txt,"a");
    if(archivo_texto==NULL){printf("Error al abrir archivo de texto");return;}
    fclose(archivo_texto);

    FILE *archivo_bin=NULL;
    char *nombre_archivo_bin="autos.bin";
    archivo_bin=fopen(nombre_archivo_bin,"rb");
    if(archivo_bin==NULL)
    {
        archivo_bin=fopen(nombre_archivo_bin,"wb");
        if(archivo_bin==NULL){printf("No se ha podido abrir el archivo por primera vez");return -1;}
        printf("Se ha creado el archivo\n");
    }else
    {
        fseek(archivo_bin,0,SEEK_END);
        cant_vehiculos=ftell(archivo_bin)/sizeof(Vehiculo);
    }

    fclose(archivo_bin);

    int opc;
    do
    {
        printf("\n");
        system("pause");
        system("cls");
        printf("Hay %d vehiculos cargados",cant_vehiculos);
        printf("\n1) Registar auto");
        printf("\n2) Listar vehiculos registrados");
        printf("\n3) Listar vehiculos multados");
        printf("\n4) Buscar vehiculos");
        printf("\n5) Editar vehiculo");
        printf("\n6) Vaciar archivo");
        printf("\n7) Salir");
        printf("\nOpcion: ");
        scanf("%d",&opc);

        switch(opc)
        {
        case 1:
            registar(archivo_bin,v,nombre_archivo_bin);
            break;
        case 2:
            listar_vehiculos(archivo_bin,v,nombre_archivo_bin);
            break;
        case 3:
            listar_multados(archivo_bin,v,nombre_archivo_bin);
            break;
        case 4:
            buscar_vehiculo(archivo_bin,v,nombre_archivo_bin);
            break;
        case 5:
            editar_vehiculo(archivo_bin,v,nombre_archivo_bin);
            break;
        case 6:
            borrar_archivo(archivo_bin,nombre_archivo_bin,nombre_archivo_txt,archivo_texto);
            break;
        case 7:
            printf("\nSaliendo del programa...");
            break;
        default:
            printf("\nNumero fuera de rango");

        }
    }while(opc!=7);
    free(v);
    v=NULL;

    return 0;
}

void registar(FILE *archivo,Vehiculo *v,char *nombre)
{
    archivo=fopen(nombre,"ab");
    if(archivo==NULL){printf("error al abrir archivo para ingresar vehiculo");return;}

    printf("Ingrese los datos del vehiculo %d",cant_vehiculos+1);

    printf("\nTipo de vehiculo: ");
    fflush(stdin);
    gets(v->vehiculo_tipo);

    printf("Patente: ");
    fflush(stdin);
    gets(v->patente);

    srand(time(NULL));
    int velociad;
    velociad=rand()%241+10;
    v->velocidad_registrada=velociad;

    if(v->velocidad_registrada>80)
    {
        char multa[]="multado";
        strcpy(v->estado,multa);
        FILE *archivo_texto=NULL;
        char *nombre_archivo_txt="Log.txt";
        archivo_texto=fopen(nombre_archivo_txt,"a");
        if(archivo_texto==NULL){printf("Error al abrir archivo de texto");return;}

        time_t t;
        struct tm *timeinfo;
        time(&t);
        timeinfo = localtime(&t);

        fprintf(archivo_texto,"A las %02d:%02d:%02d HS se registro una multa del vehiculo: ", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
        fprintf(archivo_texto,"\nVehiculo: %s\n",v->vehiculo_tipo);
        fprintf(archivo_texto,"Patente: %s\n",v->patente);
        fprintf(archivo_texto,"Estado: %s\n",v->estado);
        fprintf(archivo_texto,"Velocidad a la que conducia: %d\n\n________________\n",v->velocidad_registrada);
        fclose(archivo_texto);
    }else
    {
        char multa[]="normal";
        strcpy(v->estado,multa);
    }

    cant_vehiculos++;
    fwrite(v,sizeof(Vehiculo),1,archivo);
    fclose(archivo);
    rewind(archivo);
}

void listar_vehiculos(FILE *archivo,Vehiculo *v,char *nombre)
{
    archivo=fopen(nombre,"rb");
    if(archivo==NULL){printf("Error al abrir el archivo para ver autos");return;}
    rewind(archivo);
    while(fread(v,sizeof(Vehiculo),1,archivo))
    {
        printf("\n\nPatente: %s",v->patente);
        printf("\nEstado: %s",v->estado);
        printf("\nVelocidad: %d",v->velocidad_registrada);
        printf("\nTipo de vehiculo: %s",v->vehiculo_tipo);

    }
    fclose(archivo);
}

void listar_multados(FILE *archivo,Vehiculo *v,char *nombre)
{
    archivo=fopen(nombre,"rb");
    if(archivo==NULL){printf("error al intentar ver los vehiuculos multados");return;}

    int cant_recaudada=0;
    int cant_vehiculos_multados=0;
    int flag=0;
    while(fread(v,sizeof(Vehiculo),1,archivo))
    {
        if(strcmp(v->estado,"multado")==0)
        {
            flag=1;
            printf("\n\nPatente: %s",v->patente);
            printf("\nEstado: %s",v->estado);
            printf("\nVelocidad: %d",v->velocidad_registrada);
            printf("\nTipo de vehiculo: %s",v->vehiculo_tipo);
            cant_recaudada+=50000;
            cant_vehiculos_multados++;
        }
    }

    if(flag==0)
    {
        printf("\nNo hay vehiculos multados");
    }
    else
    {
        printf("\nHay %d vehiculos multados y la recaudacion de las multas es de %d",cant_vehiculos_multados,cant_recaudada);
    }

    fclose(archivo);
}

void buscar_vehiculo(FILE *archivo,Vehiculo *v,char *nombre)
{
    archivo=fopen(nombre,"rb");
    if(archivo==NULL){printf("error al intentar ver los vehiuculos multados");return;}

    char rta[8];
    printf("Ingrese la patente del auto a buscar: ");
    fflush(stdin);
    gets(rta);

    int flag=0;
    while(fread(v,sizeof(Vehiculo),1,archivo) && flag==0)
    {
        if(strcmp(rta,v->patente)==0)
        {
            flag=1;
            printf("Vehiculo encontrado!!");
            printf("\n\nPatente: %s",v->patente);
            printf("\nEstado: %s",v->estado);
            printf("\nVelocidad: %d",v->velocidad_registrada);
            printf("\nTipo de vehiculo: %s",v->vehiculo_tipo);
            break;
        }
    }

    if(flag==0){printf("No se ha encontrado ningun vehiculo con esa patente");return;}

    fclose(archivo);
}

void editar_vehiculo(FILE *archivo,Vehiculo *v,char *nombre)
{
    archivo=fopen(nombre,"rb+");
    if(archivo==NULL){printf("error al intentar editar los vehiuculos multados");return;}

    char rta[8];
    printf("Ingrese la patente del auto a buscar: ");
    fflush(stdin);
    gets(rta);

    int flag=0;

    while(fread(v,sizeof(Vehiculo),1,archivo) && flag==0)
    {
        if(strcmp(rta,v->patente)==0)
        {
            flag=1;
            printf("Vehiculo encontrado!!");
            printf("\n\nPatente: %s",v->patente);
            printf("\nEstado: %s",v->estado);
            printf("\nVelocidad: %d",v->velocidad_registrada);
            printf("\nTipo de vehiculo: %s",v->vehiculo_tipo);

            long pos=ftell(archivo)-sizeof(Vehiculo);
            fseek(archivo,pos,SEEK_SET);
            printf("\n\nEditando vehiculo...\n\n");

            printf("\nTipo de vehiculo: ");
            fflush(stdin);
            gets(v->vehiculo_tipo);

            printf("Patente: ");
            fflush(stdin);
            gets(v->patente);

            printf("Velocidad: ");
            fflush(stdin);
            scanf("%d",&v->velocidad_registrada);

            printf("estado: ");
            fflush(stdin);
            gets(v->estado);

            fwrite(v,sizeof(Vehiculo),1,archivo);
            break;
        }

    }

    if(flag==0){printf("No se ha encontrado ningun vehiculo con esa patente");return;}

    rewind(archivo);
    fclose(archivo);
}

void borrar_archivo(FILE *archivo,char *nombre,char *nombre_txt,FILE *archivo_txt)
{
    archivo=fopen(nombre,"wb");
    if(archivo==NULL){printf("error al eliminar datos del archivo");return;}
    cant_vehiculos=0;
    fclose(archivo);

    archivo_txt=fopen(nombre_txt,"w");
    if(archivo_txt==NULL){printf("error al eliminar datos del archivo de texto");return;}
    fclose(archivo);



}