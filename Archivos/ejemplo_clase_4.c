#include <stdio.h>
#include <stdlib.h>

int main() {
  // Your code here

  FILE* fp = NULL;
  int len;
  fp = fopen("file.txt", "w");

  fputs("Escribo una linea....", fp);

  fseek(fp, 50, SEEK_CUR);
  fputs("Escribo desplazando 50 lugares", fp);
  fseek(fp, -70, SEEK_END);
  fputs("Escribo en -70 desde el final::", fp);
  len = ftell(fp);
  printf("Len = %d", len);

  fclose(fp);
  


  return 0;
}