#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"
#include <sys/time.h>


int main()
{
    //inicialização dos dois vetores de caminho, a distância mais curta e o número de cidades
    int *caminhos, *melhor_caminho, melhor_distancia, ncidades;
    //inicialização do grafo
    GrafoPonderado *grafo;
    
    //inicialização da variável que irá calcular o tempo de execução do programa
        /*
        double elapsed_time;
        struct timeval start, end;
        //Primeira chamada da função que marca a hora exata em que o algoritmo passa por esta linha do código
        gettimeofday(&start, NULL);
        */

    //entrada do numero de cidades    
    scanf("%d", &ncidades);

    //alocação do grafo
    grafo = alocarGrafo(ncidades);

    //alocação da lista de adjacencias
    ListaDeAdjacencia **adjacencias = alocaLista(ncidades);

    //alocação dos dois vetores de caminhos
    caminhos = criaVetor(grafo->cidades);
    melhor_caminho = criaVetor(grafo->cidades);

    //leitura dos dados do grafo
    leGrafo(grafo->cidades, grafo);

    //loop que ordena o vetor de listas
    for (int i = 0; i < grafo->cidades; i++) 
    {
        ordenaLista(adjacencias[i], grafo->cidades, grafo->matriz, i);
        imprimeOrdenado(adjacencias[i], i);
    }

    //atribuição arbitraria da distância total do caminho mais curto para que ela seja posteriormente comparada com as distâncias da lista 
    melhor_distancia = 999999;

    //chamada da função que encontra o caminho mais curto
    encontraCaminho(caminhos, melhor_caminho, 1, grafo->cidades, adjacencias, &melhor_distancia);
    
    //chamada da função que imprime o caminho mais curto encontrado
    imprimeCaminho(grafo->cidades, melhor_caminho);

    //impressão da melhor distância    
    printf("Melhor distancia: %d\n", melhor_distancia);

    //liberação da memória do grafo, do vetor de listas, do vetor de caminhos e da matriz do grafo
    desalocarGrafo(grafo, adjacencias, caminhos, grafo->cidades);

    //liberação da memória do vetor que contem o caminho mais curto
    free(melhor_caminho);

    /*
        //Segunda chamada da função que marca o tempo real
        gettimeofday(&end, NULL);
        //Cálculo do tempo decorrido entre a primeira chamada e a segunda. O resultado é expresso na ordem de microssegundos
        elapsed_time = (end.tv_sec - start.tv_sec) * 1e6 + (end.tv_usec - start.tv_usec);
        //Conversão de microssegundos para milissegundos
        elapsed_time /= 1000;
        printf("Tempo gasto: %.3lf milissegundos\n", elapsed_time);
    */
    
    return 0;
}