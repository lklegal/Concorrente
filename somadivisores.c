#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    int numero = 1000000000;
    int soma = 0;

    //sequencial
    double inicio = omp_get_wtime();
    for (int i=1; i<=(int)numero/2; i++)
    {
        if (numero%i == 0)
        {
            soma += i;
        }
        
    }
    
    double fim = omp_get_wtime();
    double tempoSequencial = fim-inicio;

    //paralelo com reduction
    inicio = omp_get_wtime();
    soma = 0;

    #pragma omp parallel num_threads(4)
    {
        #pragma omp for reduction (+:soma)
        for (int i=1; i<=(int)numero/2; i++)
        {
            if (numero%i == 0)
            {
                soma += i;
            }
        
        }
    }
    
    fim = omp_get_wtime();
    double tempoParalelo = fim-inicio;
    printf("Reduction: %f\n", tempoSequencial/tempoParalelo);

    //paralelo com região crítica e agendamento estático
    inicio = omp_get_wtime();
    soma = 0;
    #pragma omp parallel num_threads(4)
    {
        int somacrit = 0;
        #pragma omp for schedule(static)
        for (int i=1; i<=(int)numero/2; i++)
        {
            if (numero%i == 0)
            {
                somacrit += i;
            }
        }
        #pragma omp critical
            soma += somacrit;
    }
    
    fim = omp_get_wtime();
    tempoParalelo = fim-inicio;
    printf("Região crítica com agendamento estático: %f\n", tempoSequencial/tempoParalelo);

    //paralelo com região crítica e agendamento dinâmico
    inicio = omp_get_wtime();
    soma = 0;
    #pragma omp parallel num_threads(4)
    {
        int somacrit = 0;
        #pragma omp for schedule(dynamic)
        for (int i=1; i<=(int)numero/2; i++)
        {
            if (numero%i == 0)
            {
                somacrit += i;
            }
        }
        #pragma omp critical
            soma += somacrit;
    }
    
    fim = omp_get_wtime();
    tempoParalelo = fim-inicio;
    printf("Região crítica com agendamento dinâmico: %f\n", tempoSequencial/tempoParalelo);
    return 0;
}