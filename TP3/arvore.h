#ifndef ARVORE_H
#define ARVORE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define STR_MAX_TAM 100
#define RED 1
#define BLACK 0


    typedef struct
    {
        char nome[STR_MAX_TAM];
        int idade;
    } Pessoa;    

    typedef struct node
    {
        Pessoa dados;
        struct node *nopai;
        struct node *esq;
        struct node *dir;
        int cor;
    } No;

    typedef struct
    {
        No *raiz;
    } RBTree;

    // arvoreInicia: inicia árvore.
    void arvoreInicia(RBTree*);

    // noCria: cria nó.
    No* noCria();

    // alocarArvore: aloca um (ou mais) TAD RBTree.
    RBTree* alocarArvore();

    // desalocarArvore: desaloca um TAD RBTree.
    void desalocarArvore(RBTree**);

    // destruirArvore: desaloca um TAD No.
    void destruirArvore(No *no);

    // leArvore: inicializa o TAD RBTree a partir de dados do terminal.
    void leArvore(RBTree*);

    // rotacaoDireita: função que realiza a rotação da árvore para a direita.
    void rotacaoDireita(RBTree*, No*);

    // rotacaoEsquerda: função que realiza a rotação da árvore para a esquerda.
    void rotacaoEsquerda(RBTree*, No*);

    // insercao: função para inserir um nó na árvore.
    void insercao(RBTree*, No*);

    // balanceamento_insercao: função que realiza o balanceamento da árvore, para o caso de uma inserção.
    void balanceamento_insercao(RBTree*, No*);

    // transplantar: faz a parte de transplantar um nó a outro passado por parâmetro
    void transplantar(RBTree *arvore, No *u, No *v);

    // minimo_direita: procura o minimo de um nó que está na direita, o que essa função faz é simplesmente ir ao máximo a esquerda possível, a fim de encontrar o nó mais próximo do nó pai
    No *minimo_direita(No *x);

    // procuraNo: procura um No com a informação "dados.idade" identica a passada por "idade_chave"
    No *procuraNo(No *root, int idade_chave);

    // remocao: faz toda a parte de remoção, chamando as funções auxiliares
    void remocao(RBTree *arvore, int idade_chave);

    // balanceamento_remocao: faz o balanceamento para o caso de uma remoção
    void balanceamento_remocao(RBTree *arvore, No *x);

    // printInOrder: função para imprimir a árvore inOrder.
    void printInOrder(No*);

    // printSpaces: imprimir espaços passados por parâmetro.
    void printSpaces(int);

    // printNo: imprime a idade da pessoa e a cor do nó.
    void printNo(No*);

    // printArvore: imprime a árvore de uma forma mais "visual" no terminal.
    void printArvore(No*, int);

    // cor: ver a cor do nó.
    char* cor(No*);

    // trocaCor: troca a cor do nó.
    void trocaCor(No*);

#endif