#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 1000000000
#define TAMANHO 1000000000

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

int maiorValorSequencial(int *indiceMaior, int vetor[], int maximo){
    int maiorValor = vetor[0];
    for (int i = 0; i < maximo; i++)
    {
        if (vetor[i] > maiorValor)
        {
            maiorValor = vetor[i];
            *indiceMaior = i;
        }
        
    }
    return maiorValor;
}

int main() {
    
    //***ÀS VEZES DÁ SEGMENTATION FAULT, NÃO FAÇO A MENOR IDEIA DO MOTIVO. MAS QUANDO NÃO DÁ, FUNCIONA***

    time_t t;
    srand(time(NULL));
    int *vetor = NULL;
    vetor = gerar_vetor_inteiro(TAMANHO);

    int maiorValor = vetor[0];
    int indiceMaiorValor = 0;

    //sequencial
    double inicio = omp_get_wtime();
    maiorValor = maiorValorSequencial(&indiceMaiorValor, vetor, TAMANHO);
    printf("Maior valor sequencial: %d, Maior índice sequencial: %d\n", maiorValor, indiceMaiorValor);
    double fim = omp_get_wtime();
    double tempoSequencial = fim-inicio;

    //paralelo
    inicio = omp_get_wtime();
    int candidatos_a_maior[] = {0, 0, 0, 0};
    int maioresIndices[] = {0, 0, 0, 0};
    
    #pragma omp parallel num_threads(4)
    {
        int id = omp_get_thread_num();
        #pragma omp for
        for (int i = 0; i < TAMANHO; i++)
        {
            if (vetor[i] > candidatos_a_maior[id])
            {
                candidatos_a_maior[id] = vetor[i];
                maioresIndices[id] = i;
            }
            
        }
    }
    maiorValor = maiorValorSequencial(&indiceMaiorValor, candidatos_a_maior, 4);
    indiceMaiorValor = maioresIndices[indiceMaiorValor];
    printf("Maior valor paralelo: %d, Maior índice paralelo: %d\n", maiorValor, indiceMaiorValor);
    fim = omp_get_wtime();
    double tempoParalelo = fim-inicio;

    printf("Speedup: %fx", tempoSequencial/tempoParalelo);

    return 0;
}