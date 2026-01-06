#ifndef FUNCS
#define FUNCS

typedef struct{
    int partida;
    int *destino;
    int *dist;
} GrafoPonderado;

GrafoPonderado *alocarGrafo(int);

int *alocaCaminho(int);

int *alocaResult(int);

int **alocaMat(int, int);

void desalocarGrafo(GrafoPonderado*, int*, int, int, int**, int*);

void leCidades(int*);

void leGrafo(int, GrafoPonderado*);

void imprimeData(int, GrafoPonderado*);

int fatorial(int);

int *criaVet(int);

void koukan(int*, int*);

void contabiliza(int[], int, int, int**, int*);

int *encontraCaminho(int, int, int**, GrafoPonderado*);

void imprimeCaminho(int, int*);


#endif