#include <stdio.h>
#include <stdlib.h>

void agregar_alumnos(FILE * archivo);
void mostar_alumnos(FILE * archivo);

int main()
{
    int eleccion = 0;
    FILE * archivo_alumnos = NULL;

    if ((archivo_alumnos = fopen("alumnos.txt", "a+")) == NULL) {
        printf("No se pudo leer el archivo");
        exit(-1);
    }

    do {
    printf("Elige una de las siguiente opciones:\n",
    "1. Agregar alumnos al archivo",
    "2. Mostar alumnos del archivo",
    "3 Salir");

    scanf("%d", &eleccion);

    switch (eleccion)
    {
    case 1:
      agregar_alumnos(archivo_alumnos);
      break;
    case 2:
      mostrar_alumnos(archivo_alumnos);
    case 3:
      break;
    default:
      system("read -p 'Comando erroneo, vuelva a ingresar un valor\n' var");
      break;
    }
    } while (eleccion != 3);

    fclose(archivo_alumnos);


    return 0;
}

void agregar_alumnos(FILE * archivo) {
  char texto[50]; // esta bien no hacer esto con malloc? es valido?
  fscanf(archivo, "%s", texto);
}

void mostrar_alumnos(FILE * archivo) {
  
}

