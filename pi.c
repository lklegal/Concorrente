#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    double pi = 0.0;
    int num_steps = 1000000000;
    double step = 1.0 / (double)num_steps;
    double inicio = omp_get_wtime();
    #pragma omp parallel num_threads(4)
    {
        double x,sum=0.0;
        int i, id, nthrds;
        id = omp_get_thread_num();
        nthrds = omp_get_num_threads();
        for (i=id,sum=0.0;i< num_steps; i=i+nthrds){
            x = (i + 0.5) * step;
            sum = sum + 4.0 / (1.0 + x*x);
        }
        #pragma omp critical
            pi+=sum*step;
    }
    double fim = omp_get_wtime();
    double tempo = fim-inicio;
    printf("%f, %f", pi, tempo);
    return 0;
}