#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double **criaMatrizXY(int count);
void LiberaMatrizXY(double **M, int count);
double **obtemMatrizA(int count, double *h);
double *obtemVetorDelta(int count, double *y, double *h);
double *obtemVetorB(int count, double *delta);
void DuplicaM(double **Mo, int count, double **Mc);
void DuplicaV(int count, double *V, double *Va);
double *Gauss(double **A, int count, double *B);

int main() {
  FILE *file;
  char check;
  int i, j, count = 0;
  double aux1, aux2; // Rever a necessidade de ter essas variaveis auxiliares
  double *x, *y, *a, *b, *c, *d, *h, *B, *S, *delta;
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

  for(i = 0; i < count; i++) {
    d[i] = y[i];
  }

  for(i = 0; i < (count - 1); i++) {
    h[i] = x[i + 1] - x[i];
  }

  A = obtemMatrizA(count - 1, h); 

  delta = obtemVetorDelta(count - 1, y, h);

  B = obtemVetorB(count - 1, delta);

  S = Gauss(A, count - 1, B);

  for(i = 0; i < (count - 1); i++) {
    a[i] = (S[i + 1] - S[i]) / (6 * h[i]);
    b[i] = S[i] / 2;
    c[i] = delta[i] - (((S[i + 1] + (2 * S[i])) / 6) * h[i]);
  }

  printf("\n");
  for(i = 0; i < (count - 1); i++) {
    printf("%lf\n", S[i]);
  }
  
  printf("\n");
  for(i = 0; i < (count - 1); i++) {
    printf("S[%d]: %.3lf | %.3lf | %.3lf | %.3lf\n", i, a[i], b[i], c[i], d[i]);
  }

  free(x);
  free(y);
  free(a);
  free(b);
  free(c);
  free(d);

  LiberaMatrizXY(A, count - 1);
  free(B);
  free(S);
  free(delta);
  
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

  for(i = 1; i < (count - 1); i++) {
    for(j = 1; j < (count - 1); j++) {
      if(i == j) {
        A[i][j - 1] = h[j - 1];
        A[i][j] = 2 * (h[j - 1] + h[j]);
        A[i][j + 1] = h[j];
      }
    }
  }

  A[0][0] = 2 * h[0];
  A[0][1] = h[0];
  A[count - 1][count - 2] = h[count - 2];
  A[count - 1][count - 1] = 2 * h[count - 1];  

  return A;
}

double *obtemVetorDelta(int count, double *y, double *h) {
  int i;
  double *delta;
  delta = (double *) malloc(sizeof(double) * count);

  for(i = 0; i < count; i++) {
    delta[i] = (y[i + 1] - y[i]) / h[i];
  }

  return delta;
}

double *obtemVetorB(int count, double *delta) {
  int i;
  double *B;
  B = (double *) malloc(sizeof(double) * count);

  for(i = 0; i < count; i++) {
    B[i] = delta[i + 1] - delta[i];
  }
  
  return B;
}

void DuplicaM(double **Mo, int count, double **Mc) {
  for (int i = 0; i < count; i++) {
    for (int j = 0; j < count; j++) {
      Mc[i][j] = Mo[i][j];
    }
  }
}

void DuplicaV(int count, double *V, double *Va) {
    for (int i = 0; i < count; i++) {
      Va[i] = V[i];
    }
}

//Tem um erro aqui!!!!!

double *Gauss(double **A, int count, double *B) {
  int i, j, k;
  double M, *x, **Mc, soma, *Va;

  x = (double *) malloc(sizeof(double) * (count - 1));
  Va = (double *) malloc(sizeof(double) * count);
  Mc = criaMatrizXY(count);

  DuplicaM(A, count, Mc);
  DuplicaV(count, B, Va);

  //Matriz triangular superior
  for(k = 0; k < (count - 1); k++) {
    for(i = (k + 1); i < count; i++) {
      M = Mc[i][k] / Mc[k][k];
      for(j = k; j < count; j++){   //Aplica o fator M em toda linha
        Mc[i][j] = Mc[i][j] - (M * Mc[k][j]);
      }
      Va[i] = Va[i] - (M * Va[k]);
    }
  }

  //Substituicao sucessiva
  for(i = (count - 1); i >= 0; i--) {
    for(j = (i + 1); j < count; j++) {
      Va[i] = Va[i] - (x[j] * Mc[i][j]);
    }
    x[i] = Va[i] / Mc[i][i];
  }

  return x;
}