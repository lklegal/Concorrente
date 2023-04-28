# OpenMP Tasks

## O que são OpenMP tasks
- OpenMP tasks são unidades de trabalho que podem ser executadas em paralelo por diferentes threads.
- OpenMP tasks permitem uma paralelização mais dinâmica e adaptativa do que os loops paralelos.

## Como utilizar
- Para utilizar OpenMP tasks, é preciso criar uma região paralela com a diretiva #pragma omp parallel .
- Dentro da região paralela, pode-se criar uma ou mais tasks com a diretiva #pragma omp task .
- Cada task tem um código associado e um ambiente de dados.
- As tasks são executadas por qualquer thread disponível na região paralela .
- As tasks podem ser sincronizadas com as diretivas #pragma omp taskwait e #pragma omp taskgroup .

## Exemplos de utilização
- Um exemplo simples de utilização de OpenMP tasks é o seguinte:

int main() {
  #pragma omp parallel
  {
    #pragma omp task
    printf("Task 1\n");
    #pragma omp task
    printf("Task 2.\n");
    return 0;
  }
}

## Qual a diferença para as OpenMP Sections
- OpenMP Sections são blocos de código que podem ser executados em paralelo por diferentes threads.
- OpenMP Sections são especificadas usando a diretiva #pragma omp sections dentro de uma região paralela ou worksharing.
- A diferença entre OpenMP Sections e OpenMP Tasks é que as sections têm um número fixo e conhecido de blocos de código, enquanto as tasks podem ser criadas dinamicamente e em qualquer quantidade.
- Além disso, as sections são atribuídas estaticamente às threads disponíveis, enquanto as tasks são atribuídas dinamicamente às threads livres.

## Quando utilizar ?
- OpenMP Tasks são úteis para paralelizar problemas que têm uma estrutura irregular ou recursiva, como árvores, grafos, divisão e conquista, etc .
