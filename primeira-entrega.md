# **Primeira entrega - Ranksort**

## Equipe

- Ana Luiza Gonçalves Torres
- Luiz Kaio Martins e Silva
- Davi Henrique Job Rodrigues
  
    **Repositório:** [GitHub](https://github.com/davi-job/Concorrente-Projeto/) 
---
## Tema

 **Implementação do algoritmo de ordenação Ranksort**

---
## Como planejamos resolver
**OpenMP** - paralelizar com o pragma omp for

**MPI** - paralelizar usando um sistema de switch com variável rank

---
## Analise de desepenho

A análise de desempenho será feita com _speedUp_. Dado que a implementação será feita de 3 formas diferentes, uma sequencial e duas paralelas, as paralelas utilizando **OpenMP** e **MPI**, em cada uma será utilizado marcadores de tempo de execução, para no fim analisar a medida do ganho de tempo.
    
    speedUp1 = Squencial / paraleloMPI
    speedUp2 = Sequencial / paraleloOpenMP

## Recursos computacionais utilizados

- Computadores pessoais
- Cluster do laboratório k04-s

## Descrição do Ranksort

Uma solução de organização de arrays onde o código pega item a item do array e percorre o mesmo contando quantos itens tem valores menores que o item selecionado, a quantidade de itens menores contada é o rank do item selecionado, então depois de atribuir um rank para todos os itens o array é organizado baseado no valor dos ranks, ou menor pro maior ou maior pro menor.