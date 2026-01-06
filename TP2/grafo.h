#ifndef FUNCS
#define FUNCS

// Struct que contém os dados do grafo
typedef struct GrafoPonderado{ 
    int cidades; 
    int **matriz;
} GrafoPonderado;

// Struct que contém os dados da lista
typedef struct ListaDeAdjacencia{ 
    int vertice;     
    int dist;
    struct ListaDeAdjacencia* proximo;
} ListaDeAdjacencia;

GrafoPonderado *alocarGrafo(int);

ListaDeAdjacencia **alocaLista(int);

void desalocarLista(ListaDeAdjacencia*);

void desalocarGrafo(GrafoPonderado*, ListaDeAdjacencia**, int*, int );

void leGrafo(int, GrafoPonderado*);

int *criaVetor(int);

void troca(int*, int*);

void encontraCaminho(int*, int*, int, int, ListaDeAdjacencia**, int*);

void ordenaLista(ListaDeAdjacencia*, int, int**, int);

void imprimeOrdenado(ListaDeAdjacencia*, int);

void imprimeCaminho(int, int*);

#endif