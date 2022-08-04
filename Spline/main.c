#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double **criaMatrizXY(int count);
void LiberaMatrizXY(double **M, int count);
double **obtemMatrizA(int count, double *h);

int main() {
  FILE *file;
  char check;
  int i, j, count = 0;
  double aux1, aux2; // Rever a necessidade de ter essas variaveis auxiliares
  double *x, *y, *a, *b, *c, *d, *h;
  double **A;

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

  for(i = 0; i < count; i++){
    fscanf(file, "%lf %lf", &x[i], &y[i]); // Guardando os valores de x e y na matriz M
  }

  fclose(file);

  for(i = 0; i < count; i++){
    printf("%.3lf %.3lf\n", x[i], y[i]); // Imprime a matriz na tela
  }

  for(i = 0; i < count; i++) {
    a[i] = y[i];
  }

  for(i = 0; i < (count - 1); i++) {
    h[i] = x[i + 1] - x[i];
  }

  A = obtemMatrizA(count, h);

  free(x);
  free(y);
  free(a);
  free(b);
  free(c);
  free(d);

  LiberaMatrizXY(A, count);
  
  return 0;
}

double **criaMatrizXY(int count){ // Cria matriz M com dimensões count x count
  int i;
  double **M;
  
  M = (double **) malloc(sizeof(double *) * count);
  for(i = 0; i < count; i++) {
    M[i] = (double *) malloc(sizeof(double) * count);
  }
  
  return M;
}

void LiberaMatrizXY(double **M, int count){ // Da free na matriz M
  int i;
  
  for(i = 0; i < count; i++)
    free(M[i]);
  free(M);
}

double **obtemMatrizA(int count, double *h) {
  int i = 0, j = 0;
  double **A;
  A = criaMatrizXY(count);

  for(i = 1; i < count; i++) {
    for(j = 1; j < count; j++) {
      A[i][j] = 0;
    }
  }

  // ------------Pré processamento------------
  A[0][0] = 2 * h[0];
  A[0][1] = h[0];
  A[count - 1][count - 2] = h[count - 2];
  A[count - 1][count - 1] = h[count - 1];
  // -----------------------------------------
  
  for(i = 1; i < (count - 1); i++) {
    for(j = 1; j < (count - 1); j++) {
      if(i == j) {
        A[i][j - 1] = h[j - 1];
        A[i][j] = 2 * (h[j - 1] + h[j]);
        A[i][j + 1] = h[j];
      }
    }
  }

  return A;
}