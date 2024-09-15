#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *archivo1=NULL;
    char * nombrearchivo="programacion1.txt";
    char texto[1000];
    int findearchivo=0;

    archivo1=fopen(nombrearchivo, "r");

    if (archivo1==NULL)
    {
        printf("Error al abrir el archivo...");
        return -1;
    }

    fgets(texto, 1000, archivo1);
    printf("\nEl archivo dice lo siguiente: %s\n", texto);

    /*

    while(findearchivo!=EOF)
    {
        printf("\n\t%s", texto);
        findearchivo=fscanf(archivo1, " %[^\n]", &texto);
    }
    fclose(archivo1);

    printf("\n\n\nArchivo cerrado...");
*/

    return 0;
}
