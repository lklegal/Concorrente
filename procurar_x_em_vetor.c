#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100
#define TAMANHO 100000000

double *gerar_vetor(int n);
int *gerar_vetor_inteiro(int n);

int main() {
    time_t t;
    srand(time(NULL));
    int *vetor = NULL;
    vetor = gerar_vetor_inteiro(TAMANHO);

    int numeroProcurado = 22;
    int count = 0;

    //sequencial
    double inicio = omp_get_wtime();
    for (int i = 0; i < TAMANHO; i++)
    {
        if (vetor[i] == numeroProcurado)
        {
            count++;
        }
        
    }
    printf("%d\n", count);
    double fim = omp_get_wtime();
    double tempoSequencial = fim-inicio;

    //paralelo
    inicio = omp_get_wtime();
    count = 0;
    #pragma omp parallel num_threads(4)
    {
        #pragma omp for reduction (+:count)
        for (int i = 0; i < TAMANHO; i++)
        {
            if (vetor[i] == numeroProcurado)
            {
                count++;
            }
            
        }
    }
    printf("%d\n", count);
    fim = omp_get_wtime();
    double tempoParalelo = fim-inicio;

    printf("Speedup: %fx", tempoSequencial/tempoParalelo);

    return 0;
}

int *gerar_vetor_inteiro(int n) {
    int *vetor;
    int i;
    vetor = (int *)malloc(sizeof(int) * n);
    for (i=0;i<n;i++) {
        int num = (rand() % MAX);
        vetor[i] = num;
    }
    return vetor;
}