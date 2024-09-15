#include <stdio.h>
#include <stdlib.h>

#define TAM 10

int main()
{
    int vec[TAM], adic, j, i, k;
    srand(time(NULL));

    FILE *arch1 = NULL;
    char *nombreArch = "programacion1.txt";

    for (int i=0; i<TAM; i++){
        vec[i] = rand()% 100;
        printf("[%d] %d\n", i+1,vec[i]);
    }

    arch1 = fopen(nombreArch, "w"); // w abre arch escritura, si no existe se crea. si devuelve null, problem!

    if (arch1 == NULL)
    {
        printf("ERROR AL ABRIR EL ARCHIVO");

        return -1;
    }

    for(int i=0; i<TAM; i++){
        fprintf(arch1, "%d\n", vec[i]);
    }

    fprintf(arch1, "\n");

    // shell
    int intervalo=TAM/2;

 while (intervalo > 0)
 {
     for (i=intervalo;i<TAM;i++)
     {
         j=i-intervalo;
         while (j>=0)
         {
            k=j+intervalo;
             if (vec[j] <= vec[k]){
                 j=-1;
            }
             else
            {
                 int temp;
                 temp=vec[j];
                 vec [j]=vec[k];
                 vec [k]=temp;
                j-=intervalo;
            }
        }
    }
    intervalo=intervalo/2;
}


    printf("\nvector ordenado:\n");

    for (int i=0; i<TAM; i++){
        printf("[%d] %d\n", i+1,vec[i]);
    }

    for(int i=0; i<TAM; i++){
        fprintf(arch1, "%d\n", vec[i]);
    }

    fclose(arch1);

    printf("\n archivo guardado y cerrado bb");

}
