#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int *gerar_vetor_binario(int n) {
  int *vetor;
  int i;
  vetor = (int *)malloc(sizeof(int) * n);
  for (i=0;i<n;i++) {
    int num = rand() % 2;
    vetor[i] = num;
  }
  return vetor;
}

void imprimir_vetor(int *vetor, int n) {
  int i;
  for (i=0;i<n;i++) {
    printf("%d ", vetor[i]);
  }
  printf("\n");
}

int main() {
  int n = 100000000; // Tamanho do vetor binário
  int p; // Número de processos
  int id; // Identificador do processo
  int *vetor; // Vetor binário
  int *subvetor; // Subvetor de cada processo
  int subn; // Tamanho do subvetor
  int count; // Número de 1's no subvetor
  int total; // Número total de 1's no vetor
  int paridade;
  
  MPI_Comm_size(MPI_COMM_WORLD, &p);
  MPI_Comm_rank(MPI_COMM_WORLD, &id);
  if (id == 0) {
    vetor = gerar_vetor_binario(n);
    printf("Vetor binário gerado:\n");
    imprimir_vetor(vetor, n);
  }
  subn = n / p;
  subvetor = (int *)malloc(sizeof(int) * subn);
  MPI_Scatter(vetor, subn, MPI_INT, subvetor, subn, MPI_INT, 0, MPI_COMM_WORLD); 
  count = 0;
  for (int i=0;i<subn;i++) {
    if (subvetor[i] == 1) {
      count++;
    }
  }
  MPI_Reduce(&count, &total, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
  if (id == 0) { // Processo 0 verifica a paridade do vetor
    printf("Número total de 1's no vetor: %d\n", total);
    if (total % 2 == 0) {
      paridade = 0;
    } else {
      paridade = 1;
    }
    printf("Paridade do vetor: %d\n", paridade);
    vetor[n] = paridade;
    n++;
    printf("Vetor binário com paridade:\n");
    imprimir_vetor(vetor, n);
  }
  MPI_Gather(&paridade, 1, MPI_INT, vetor, 1, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Finalize();
  return 0;
}
