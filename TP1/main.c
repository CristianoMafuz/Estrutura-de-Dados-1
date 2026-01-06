#include <stdio.h>
#include "grafo.h"

int main(){
    int cidades, count = -1;

    leCidades(&cidades);
    int n = fatorial(cidades - 1);
    int *vet = criaVet(cidades);
    int **mat = alocaMat(cidades, n);
    GrafoPonderado *data = alocarGrafo(cidades);
    leGrafo(cidades, data);
    contabiliza(vet, 1, cidades, mat, &count);
    int *caminho = encontraCaminho(cidades, n, mat, data);

    /*for (int i = 0; i < n; i++) { // como funciona
        for (int j = 0; j < cidades + 3; j++) {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }*/

    imprimeCaminho(cidades, caminho);
    desalocarGrafo(data, vet, cidades, n, mat, caminho);

    return 0;
}