#include "grafo.h"
#include <stdio.h>
#include <stdlib.h>

    // Função que aloca dinamicamente um grafo
    GrafoPonderado *alocarGrafo(int cidades)
    { 
        // Alocação a struct
        GrafoPonderado *grafo = malloc(sizeof(GrafoPonderado));

        // Definção do número de cidades
        grafo->cidades = cidades; 

        // Alocação a matriz de adjacência
        grafo->matriz = malloc(cidades * sizeof(int *));
        
        for (int i = 0; i < cidades; i++) 
        {   
            //Alocação de cada elemento da matriz
            grafo->matriz[i] = malloc(cidades * sizeof(int));
        }

        return grafo;
    }

    //Função que aloca dinamicamente um vetor de listas de adjacências
    ListaDeAdjacencia** alocaLista(int n) 
    {
        // Alocação do vetor n listas
        ListaDeAdjacencia** lista = (ListaDeAdjacencia**) malloc(n * sizeof(ListaDeAdjacencia*));

        // Verifica se a alocação foi bem-sucedida
        if (lista != NULL) 
        {
            // Inicializa cada elemento da lista
            for (int i = 0; i < n; i++) 
            {
                lista[i] = (ListaDeAdjacencia*) malloc(sizeof(ListaDeAdjacencia));
            }
        }

        // Retorna o ponteiro para o array alocado 
        return lista;
    }


    //Função que libera a memória de uma lista de adjacências. No caso deste trabalho, a função irá liberar um espaço do vetor de listas
    void desalocarLista(ListaDeAdjacencia *lista)
    {
        //auxiliares que irão percorrer a lista
        ListaDeAdjacencia *pAux = lista;
        ListaDeAdjacencia *pAux2;

        //enquanto não chegar em NULL(final da lista) a memória continuará sendo liberada
        while(pAux != NULL)
        {
            pAux2 = pAux -> proximo;
            free(pAux);
            pAux = pAux2;
        }
    }


    // Função que desaloca um grafo
    void desalocarGrafo(GrafoPonderado *grafo, ListaDeAdjacencia **adjacencias, int *caminhos, int cidades)
    {
        //Liberação da memória de cada um dos índices do vetor de listas
        for (int i = 0; i < cidades; i++)
            desalocarLista(adjacencias[i]);

        //Desalocação do vetor de listas
        free(adjacencias);

        //Desalocação do vetor de possíveis caminhos
        free(caminhos);
        caminhos = NULL;

        // Desalocação das linhas matriz de adjacência do grafo
        for (int i = 0; i < cidades; i++) 
        {
            free(grafo->matriz[i]);
            grafo->matriz[i] = NULL;
        }

        //Desalocação final da matriz
        free(grafo->matriz);
        grafo->matriz = NULL;

        // Desaloca o grafo
        free(grafo);
        grafo = NULL;
    }


    //Função que lê os dados do grafo
    void leGrafo(int cidades, GrafoPonderado *grafo)
    { 
        //auxiliares que apenas irão receber os dois primeiros números 
        int k, l;
        for (int i = 0; i < cidades; i++)
        {
            for (int j = 0; j < cidades; j++)
            {
                scanf(" %d %d", &k, &l);
                //preenchimento da matriz do grafo
                scanf(" %d", &grafo->matriz[k][l]);
            }
        }
    }

    /* Função que aloca um vetor e o preenche com o número de todas as cidades. Essa função será utilizda para armazenar caminhos, sendo que
    Cada caminho parte da cidade 0 e ao final também volta para a cidade 0. Por isso, para que o último elemento seja 0, 
    é necessário que esse vetor tenha o tamanho do número de cidades + 1.
    */

    int *criaVetor(int cidades)
    { 
        //alocação dinâmica do vetor
        int *vet = malloc((cidades+1) * sizeof(int));
        
        for (int i = 0; i < cidades; i++) 
        {
            //preenchimento do vetor com o índice i
            vet[i] = i;
        }
        //preenchimento da última posição com 0
        vet[cidades] = 0;
        return vet;
    }

    // Função de troca simples
    void troca(int *x, int *y)
    { 
        int temp = *x;
        *x = *y;
        *y = temp;
    }

    /* Função recursiva que encontra o caminho com a menor distância. A função recebe um vetor que irá computar todos os caminhos possíveis,
    um vetor que irá armazenar o melhor caminho encontrado, duas variáveis do tipo int que irão servir de parâmetro para inicio/fim da recursão,
    a lista de adjacências, que possui todas as distâncias entre as cidades, e uma variável do tipo int que irá registrar qual foi a distância
    mais curta com base no melhor caminho.*/

    void encontraCaminho(int *caminhos, int* melhor_caminho, int inicio, int fim, ListaDeAdjacencia **adjacencias, int *melhor_distancia)
    {
        //variável que irá somar as distâncias entre cidades
        int distancia_total;
        
        //variável auxiliar que irá percorrer o vetor de adjacências 
        ListaDeAdjacencia *temp;

        /*
        quando inicio = fim, a função entra no caso base, o que significa que a recursão chegou ao fim e 
        uma possibilidade de caminho foi computada no vetor de caminhos.
        */
        if (inicio == fim) 
        {   
            //a variável que somará as distâcias é inicializada com zero
            distancia_total = 0;

            //loop que irá as distâncias do caminho 
            for(int i = 0; i < fim; i++)
            {   
                /*
                a variavel temporária precisa receber o indice do vetor de listas com base no numero do vetor de caminhos. Por exemplo,
                se o vetor de caminhos computou o caminho [0,1,2,3,0], na primeira iteração, a variável temporária precisa 
                começar recebendo o indice de listas 0, que é de onde parte o caixeiro, e percorrer a lista até encontrar o segundo vértice,
                que é a cidade destino, no caso, cidade 1. Desse modo, a cada iteração, o programa tem a cidade de onde o caixeiro parte
                e a cidade destino que é o próximo elemento do vetor. Por fim, se a distância entre as duas cidades for diferente de zero, 
                então a distância precisa ser somada. Caso a distâncias entre duas cidades seja igual a zero, significa que não há caminho
                entre essas duas cidades, e portanto, o caminho computado não pode ser uma solução e deve ser descartado.
                */
                temp = adjacencias[caminhos[i]];

                //percorrendo a lista até encontrar o elemento do caminho
                while(temp->vertice != caminhos[i+1])
                {
                    temp = temp->proximo;
                }

                //verificação que valida se a distância entre as cidades é zero ou não
                if(temp->dist == 0)
                    return;
                else
                    distancia_total += temp->dist;
            }
            
            //Se ao final do processo a distância encontrada for menor que a anterior, significa que o caminho é melhor
            if(distancia_total < *melhor_distancia)
            {
                //atribuição da melhor distância
                *melhor_distancia = distancia_total;
                //atribuição do caminho mais curto encontrado
                for(int i = 0; i < fim; i++)
                    melhor_caminho[i] = caminhos[i];
            }
        }

        /*
        Parte da função onde ocorre a recursividade. O loop abaixo irá realizar trocas sucessivas do vetor de caminhos para que as 
        possibilidades sejam computadas. A primeira chamada da função troca irá embaralhar o vetor toda vez que a variável i for diferente
        da variável início, e quando as variáveis forem iguais a função de troca irá trocar números iguais e nada acontece. Já a segunda chamada
        da função troca irá destrocar os números para que else sejam reembaralhados posteriormente. 
        */
        else
        {
            for (int i = inicio; i < fim; i++) 
            {
                troca(&caminhos[inicio], &caminhos[i]);
                encontraCaminho(caminhos,melhor_caminho, inicio + 1, fim, adjacencias, melhor_distancia);
                troca(&caminhos[inicio], &caminhos[i]);
            }
        }
    }

    /*Função que ordena o vetor de listas de adjacencias com base na menor distância entre cidades. A função não recebe o vetor de listas, 
    mas sim um elemento desse vetor, que é uma lista. Ela também recebe o número de cidades, a matriz do grafo e o vértice que 
    está sendo ordenado. Assim, a função irá criar espaços novos para cada uma das listas e adicionar as adjacências dos respectivos vértice 
    de maneira já ordenada. Vale ressaltar que o método de ordenação aqui utilizado foi o Selection Sort, que para cada iteração,
    percorre toda a lista, seleciona o menor valor encontrado e insere no começo da lista.*/
    void ordenaLista(ListaDeAdjacencia *adjacencias, int cidades, int **matriz, int vertice) 
    {
        //Loop que irá gerar cada um dos parêntesis da lista de adjacencias do vértice atual.
        for (int i = 0; i < cidades; i++) 
        {
            /*
            as variáveis abaixo irão ser utilizadas na comparação das distâncias entre os vértices(cidades) e são inicializadas com valores
            arbitrários. A variável aux_dist é a variável que irá receber a menor distância e a variável aux_pos recebe em qual vértice 
            essa distância se encontra, ou seja, essas variáveis receberão a cidade mais próxima da atual.
            */
            int aux_dist = 100, aux_pos = -1;

            //a lista em análise precisa ser percorrida todas as vezes para encontrar a menor distância, por isso a necessidade de outro loop
            for (int j = 0; j < cidades; j++) 
            {
                //variável temporária que irá percorrer a lista encadeada
                ListaDeAdjacencia *temp = adjacencias;

                /*
                variável que irá verificar se a distância encontrada é zero, que significa que o vértice em análise é a própria cidade.
                Esse verificador cumpre a função de impedir que a distância entre uma cidade e ela mesma seja computada outras vezes,
                pois 0 seria a menor distância possível entre duas cidades.
                */
                int verificador_0 = 0; 

                if(i != 0)
                {
                    while (temp != NULL) 
                    {
                        if (temp->vertice == j) 
                        {
                            //o verificador passa a ter valor 1 quando já computou a distância 0  
                            verificador_0 = 1;
                            break;
                        }
                        temp = temp->proximo;
                    }
                }
                //comparação entre a distância da matriz de adjacências e a auxiliar de distância
                if (matriz[vertice][j] < aux_dist && !verificador_0) 
                {
                    //atribuição da menor distância e a posição do vértice às auxiliares
                    aux_dist = matriz[vertice][j];
                    aux_pos = j;
                }
            }

            // Adição do novo nó à lista. caso seja a primeira iteração, a lista está na cabeça e já foi alocada
            if (i == 0) 
            {
                //alocação do novo nó e atribuição dos vértices e distâncias
                adjacencias->dist = aux_dist;
                adjacencias->vertice = aux_pos;
                adjacencias->proximo = NULL;
            } 
            // Caso não seja a primeira iteração, a lista precisa ser percorrida antes de ser adicionado um novo nó.
            else 
            {
                ListaDeAdjacencia *temp2 = adjacencias;
                while (temp2->proximo != NULL)
                {
                    temp2 = temp2->proximo;
                }
                //alocação do novo nó e atribuição dos vértices e distâncias
                temp2->proximo = (ListaDeAdjacencia*)malloc(sizeof(ListaDeAdjacencia));;
                temp2->proximo->dist = aux_dist;
                temp2->proximo->vertice = aux_pos;
                temp2->proximo->proximo = NULL;
            }
        }
    }

    // Função que imprime a lista de adjacências depois de ordenada
    void imprimeOrdenado(ListaDeAdjacencia *adjacencias, int indice) 
    {
        printf("Adjacencias do vertice %d:", indice);
        //variável temporária que irá percorrer a lista
        ListaDeAdjacencia *temp = adjacencias;

        while(temp != NULL)
        {
            //impressão do vértice e da distância
            printf(" (%d, %d) ->", temp->vertice, temp->dist);
            temp = temp->proximo;
        }
        printf(" NULL\n");
    }

    // Função que imprime o caminho com a melhor distância encontrada
    void imprimeCaminho(int cidades, int *melhor_caminho) 
    { 
        printf("Melhor caminho: ");
        //impressão dos elementos do vetor caminho
        for (int i = 0; i <= cidades; i++)
        {
            printf("%d ", melhor_caminho[i]);
        }
        printf("\n");
    }