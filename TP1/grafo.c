#include "grafo.h"
#include <stdio.h>
#include <stdlib.h>

GrafoPonderado *alocarGrafo(int cidades){
    GrafoPonderado *vet = malloc(cidades * sizeof(GrafoPonderado));
    for (int i = 0; i < cidades; i++){
        vet[i].dist = malloc(cidades * sizeof(int));
        vet[i].destino = malloc(cidades * sizeof(int));
    }
    
    return vet;    
}

int *alocaCaminho(int cidades){
    int *caminho = malloc(cidades * sizeof(int));
    return caminho;
}

int *alocaResult(int n){
    int *vet = calloc(n, sizeof(int));
    return vet;
}

int **alocaMat(int cidades, int n){
    int **mat = malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++){
        mat[i] = calloc((cidades + 3), sizeof(int));
    }
    
    return mat;
}

void desalocarGrafo(GrafoPonderado *data, int *vet, int cidades, int n, int **mat, int *caminho){
    for (int i = 0; i < cidades; i++){
        free(data[i].dist);
        free(data[i].destino);
    }
    free(data);
    free(vet);
    free(caminho);

    for (int i = 0; i < n; i++){
        free(mat[i]);
    }
    free(mat);
}

void leCidades(int *cidades){
    scanf(" %d", cidades);
}

void leGrafo(int cidades, GrafoPonderado *data){
    for (int i = 0; i < cidades; i++)
        for (int j = 0; j < cidades; j++)
            scanf(" %d %d %d", &data[i].partida, &data[i].destino[j], &data[i].dist[j]);
}

int *criaVet(int cidades) {
    int *vet = malloc(cidades * sizeof(int));
    for (int i = 0; i < cidades; i++) {
        vet[i] = i;
    }
    return vet;
}

int fatorial(int n){
    if(n == 0)
        return 1;
    else{
        n *= fatorial(n - 1);
    }
    return n;
}

void koukan(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

void contabiliza(int vet[], int start, int cidades, int **mat, int *count) {
    if (start == cidades) {
        (*count)++;
        mat[*count][0] = *count;
        for (int i = 0; i < cidades; i++) {
            mat[*count][i + 1] = vet[i];
        }
    } else {
        for (int i = start; i < cidades; i++) {
            koukan(&vet[start], &vet[i]);
            contabiliza(vet, start + 1, cidades, mat, count);
            koukan(&vet[start], &vet[i]); // backtrack
        }
    }
}

int *encontraCaminho(int cidades, int n, int **mat, GrafoPonderado *data){
    int aux = 100;
    int *caminho = malloc((cidades + 2) * sizeof(int));
    for (int i = 0; i < n; i++){
        int result = 0;
        for (int j = 1; j <= cidades; j++) {
            if(data[mat[i][j]].dist[mat[i][j+1]] != 0)
                result += data[mat[i][j]].dist[mat[i][j+1]];
            else{
                result = 0;
                break;
            }
        }
        if(result != 0){
            mat[i][cidades + 2] = result;
            if(aux > mat[i][cidades + 2]){
                aux = mat[i][cidades + 2];
                for (int k = 0; k <= cidades; k++){
                    caminho[k] = mat[i][k + 1];
                }
                caminho[cidades + 1] = aux;
            }
        }
    }
    
    return caminho;
}

void imprimeCaminho(int cidades, int *caminho){
    for (int i = 0; i <= cidades; i++){
        printf("%d ", caminho[i]);
    }
    printf("\n%d\n", caminho[cidades + 1]);
    
}
