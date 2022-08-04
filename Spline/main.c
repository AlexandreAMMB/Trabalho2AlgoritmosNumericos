#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/*double **criaMatrizXY(int count);
void LiberaMatrizXY(double **M, int count);
double **criaMatrizCoeficientes(int count);
void LiberaMatrizCoeficientes(double **C, int count);*/

int main() {
  FILE *file;
  char check;
  int count = 0;
  double aux1, aux2; // Rever a necessidade de ter essas variaveis auxiliares
  double *x, *y, *a, *b, *c, *d, *h;
  //double **M, **C;

  char *path = "marcos1.dat";
  //char *path = "grupo1.dat";
  //char *path = "grupo2.dat";
  //char *path = "grupo3.dat";
  //char *path = "grupo4.dat";

  if((file = fopen(path, "r")) == NULL){
    printf("Problemas para abrir o arquivo\n");
  } else { // Problemas de guradar o dado em variaveis auxiliares
    while( (check = fscanf(file, "%lf %lf", &aux1, &aux2)) != EOF) { // Descobrindo qnts linhas o arquivo tem
      count++; // Variavel que conta o numero de linhas do arquivo
    }
  }

  rewind(file); // Reposionando o ponteiro para o inicio do arquivo

  x = (double *) malloc(sizeof(double) * count);
  y = (double *) malloc(sizeof(double) * count);

  a = (double *) malloc(sizeof(double) * count);
  b = (double *) malloc(sizeof(double) * (count - 1));
  c = (double *) malloc(sizeof(double) * count);
  d = (double *) malloc(sizeof(double) * (count - 1));
  h = (double *) malloc(sizeof(double) * (count - 1));
  
  //M = criaMatrizXY(count); // Criando a matriz com "count" linhas e 2 colunas
  //C = criaMatrizCoeficientes(count);

  for(int i = 0; i < count; i++){
    fscanf(file, "%lf %lf", &x[i], &y[i]); // Guardando os valores de x e y na matriz M
  }

  fclose(file);

  for(int i = 0; i < count; i++){
    printf("%.3lf %.3lf\n", x[i], y[i]); // Imprime a matriz na tela
  }

  for(int i = 0; i < (count - 1); i++) {
    a[i] = y[i];
    h[i] = x[i + 1] - x[i];
  }
  a[count] = y[count];

  

  free(x);
  free(y);
  free(a);
  free(b);
  free(c);
  free(d);

  //LiberaMatrizXY(M, count);
  //LiberaMatrizCoeficientes(C, count);
  
  return 0;
}

/*double **criaMatrizXY(int count){ // Cria matriz M com "count" linhas e 2 colunas
  double **M;
  
  M = (double **) malloc(sizeof(double *) * count);
  for(int i = 0; i < count; i++) {
    M[i] = (double *) malloc(sizeof(double) * 2);
  }
  
  return M;
}

void LiberaMatrizXY(double **M, int count){ // Da free na matriz M
  for(int i = 0; i < count; i++)
    free(M[i]);
  free(M);
}

double **criaMatrizCoeficientes(int count){ // Cria matriz C com "count - 1" linhas e 4 colunas
  double **C;
  
  C = (double **) malloc(sizeof(double *) * (count - 1));
  for(int i = 0; i < count; i++) {
    C[i] = (double *) malloc(sizeof(double) * 4);
  }
  
  return C;
}

void LiberaMatrizCoeficientes(double **C, int count){ // Da free na matriz C
  for(int i = 0; i < (count - 1); i++)
    free(C[i]);
  free(C);
}*/