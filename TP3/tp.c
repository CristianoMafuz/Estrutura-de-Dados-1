#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"

    int main()
    {   
        int op, n_testes;
        RBTree *arvore = alocarArvore(); // Alocando árvore

        scanf("%d", &op); // Recebendo o código de operação

        while(op != 0) // Enquanto o código for diferente de "0", o "while" vai iterar
        {
            if(op == 1) // Caso 1 -> inserção
            {
                scanf("%d", &n_testes); // Recebendo o número de inserções

                for(int i = 0; i < n_testes; i++)
                {
                    leArvore(arvore); // Executa a função principal para quantas pessoas diferentes forem necessárias, sendo que nessa função é executada desde criação do nó, a inserção e balanceamento
                }
            }
            else if(op == 2) // Caso 2 -> impressão da árvore
            {
                // printf("Dados inOrder:\n");
                // printInOrder(arvore->raiz); // Imprime "InOrder"
                //imprimir a árvore:
                printf("\n"); // Dá um espaço para ficar mais visível
                printArvore(arvore->raiz, 0); // Imprime a árvore de uma forma mais visual, parecido com os livros didáticos
                printf("\n");
            }
            else if(op == 3) // Caso 3 -> remoção
            {
                int idade_chave; // Recebe a idade da pessoa a ser removida (única informação relevante)
                scanf(" %d", &idade_chave); // Escaneando
                remocao(arvore, idade_chave); // Faz toda a tarefa de remoção, inclusive o balanceamento
            }


            scanf("%d", &op); // Recebe novamente a opreação            
        }

        // printf("Dados inOrder:\n");
        // printInOrder(arvore->raiz);
        // printf("\n");
        //imprimir a árvore:
        printArvore(arvore->raiz, 0);
        printf("\n");

        desalocarArvore(&arvore);


        return 0;
    }