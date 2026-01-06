#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"

    // arvoreInicia: inicia árvore.
    void arvoreInicia(RBTree* arvore) // Iniciando a Árvore
    {
        arvore->raiz = NULL; //a raiz recebe NULL
    }

    // noCria: cria nó.
    No* noCria() // Alocando o Nó
    {
        //todos os ponteiros de pai e filhos à esquerda e direita recebem NULL
        No* pAux = (No*) malloc(sizeof(No));
        pAux -> esq = NULL;
        pAux -> dir = NULL;
        pAux -> nopai = NULL;
        pAux -> cor = BLACK; // Apenas para fins didáticos, pois todo no "nulo" é considerado preto
        return pAux;
    }

    // alocarArvore: aloca um (ou mais) TAD RBTree.
    RBTree* alocarArvore() // Alocando a Árvore
    {
        RBTree *arvore = (RBTree*) malloc(sizeof(RBTree));
        if (arvore != NULL) {
            arvoreInicia(arvore);
        }

        return arvore;
    }

    // desalocarArvore: desaloca um TAD RBTree.
    void desalocarArvore(RBTree **arvore) // Liberando a Árvore
    {
        if((*arvore)->raiz != NULL)
            destruirArvore((*arvore)->raiz);

        free(*arvore);
    }

    // destruirArvore: desaloca um TAD No.
    void destruirArvore(No *no) // Liberando o Nó e seus descendentes, por chamadas recursivas
    {
        if(no->dir != NULL)
            destruirArvore(no->dir); // <- chamada recursiva à direita
        if(no->esq != NULL)
            destruirArvore(no->esq); // <- chamada recursiva à esquerda

        free(no); // Por fim, libera o nó ascendente
    }

    // leArvore: inicializa o TAD RBTree a partir de dados do terminal.
    void leArvore(RBTree *arvore) // Função principal, lê os dados passados pelo usuário e insere, além de executar o balanceamento
    {
        No *novo = noCria(); // Alocando um nó

        if (novo == NULL) {
            // Tratar erro de alocação de memória para o novo nó
            return;
        }

        if (scanf("%s", novo->dados.nome) != 1) {
            // Tratar erro de leitura de string
            free(novo);
            return;
        }

        if (scanf(" %d", &novo->dados.idade) != 1) {
            // Tratar erro de leitura de inteiro
            free(novo);
            return;
        }

        insercao(arvore, novo); // Execução da inserção
        balanceamento_insercao(arvore, novo); // Execução do balanceamento
    }
  
    // rotacaoDireita: função que realiza a rotação da árvore para a direita.
    void rotacaoDireita(RBTree *arvore, No *no) 
    {
        No *aux = no->esq; //aux recebe o filho a esquerda do nó
        no->esq = aux->dir; //a esquerda do nó vira o sobrinho a direita do filho a equerda
    
        if (aux->dir != NULL) //se o sobrinho não for nulo, o pai é o próprio nó
            aux->dir->nopai = no;
    
        aux->nopai = no->nopai; //o pai de aux é o pai do nó
    
        // Se o no é a raiz
        if (no->nopai == NULL)
            arvore->raiz = aux; //a raiz da arvore passa a ser o filho da esquerda
    
        //se o nó é o filho da esquerda do pai
        else if (no == no->nopai->esq)
            no->nopai->esq = aux; //o irmao da esqueda vira o filho da esquerda do nó
    
        else
            no->nopai->dir = aux; //caso contrario, o irmao da direita vira o filho da esquerda do nó
    
        aux->dir = no; //o filho da direita do filho da esquerda do nó vira o próprio nós
        no->nopai = aux; //o pai do nó vira o filho da esquerda do nó
    }
    
    // rotacaoDireita: função que realiza a rotação da árvore para a esquerda.
    void rotacaoEsquerda(RBTree *arvore, No *no) 
    {
        No *aux = no->dir; //aux recebe o filho a direita do nó
        no->dir = aux->esq; //a direita do nó vira o sobrinho a esquerda do filho a direita
    
        if (aux->esq != NULL) //se o sobrinho não for nulo, o pai é o próprio nó
            aux->esq->nopai = no;
    
        aux->nopai = no->nopai; //o pai de aux é o pai do nó
    
        // Se no é a raiz
        if (no->nopai == NULL)
            arvore->raiz = aux; //a raiz da arvore passa a ser o filho da direita
    
        //se o nó é o filho da esquerda do pai
        else if (no == no->nopai->esq)
            no->nopai->esq = aux; //o irmao da esqueda vira o filho da direita do nó
    
        else
            no->nopai->dir = aux; //caso contrario, o irmao da direita vira o filho da direita do nó
    
        aux->esq = no; //o filho da esquerda do filho da direita do nó vira o próprio nós
        no->nopai = aux; //o pai do nó vira o filho da direita do nó
    }
    
    // insercao: função para inserir um nó na árvore.
    void insercao(RBTree *arvore, No *no)
    {
        No *aux = NULL, *procura = arvore->raiz;

        while (procura != NULL) // Procurar o até ser nulo, portanto "aux" armazena o nó anterior, que é o que queremos
        {
            aux = procura; // "aux" sempre recebendo o "procura" para ao final ficar com o "procura" da iteração anterior
            if (no->dados.idade < procura->dados.idade)
                procura = procura->esq;
            else
                procura = procura->dir;
        }

        no->nopai = aux; // O pai do nó a ser inserido recebe o "aux"

        if (aux == NULL) // Caso o nó seja a própria raiz
            arvore->raiz = no;

        else if (no->dados.idade < aux->dados.idade) // Decidir se vai para a direita ou para a esquerda
            aux->esq = no;

        else
            aux->dir = no;


        no->dir = NULL;
        no->esq = NULL;
        no->cor = RED; // Declara os filhos como "NULL" e colore o nó de vermelho
    }

    // balanceamento_insercao: função que realiza o balanceamento da árvore, para o caso de uma inserção.
    void balanceamento_insercao(RBTree *arvore, No *no)
    {
        while (no != arvore->raiz && no->nopai->cor == RED)
        {
            No *pai = no->nopai; // Gerando um ponteiro para o nó pai para uma mais fácil visualização
            No *vo = pai->nopai; // Gerando um ponteiro para o nó avô para uma mais fácil visualização

            if (pai == vo->esq) // Caso o pai seja o filho esquerdo do avô
            {
                No *tio = vo->dir; // Gerando um ponteiro para o nó tio para uma mais fácil visualização
                if (tio && tio->cor == RED) // Caso 1 -> tio == RED
                {
                    trocaCor(vo); // troca a cor do avo, do pai e do tio
                    no = vo; // no recebe seu avo
                }
                else
                {
                    if (no == pai->dir) // Caso 2 -> tio == preto (formato de joelho ou triiangular)
                    {
                        no = pai; // no recebe seu pai
                        rotacaoEsquerda(arvore, no); // Rotação a esquerda passando "no" (que agora é o seu pai)
                    }

                    // perceba que não tem um "else" aqui, ou seja, o caso 2 pressupõe o caso 3

                    no->nopai->cor = BLACK; // Caso 3 -> tio == preto (linha reta)
                    vo->cor = RED; // vo recebe a cor vermelha
                    rotacaoDireita(arvore, vo); // Rotação a direita passando "vo" (que agora é o seu pai)
                }
            }
            else if (pai == vo->dir) // Caso o pai seja o filho direito do avô
            {
                No *tio = vo->esq; // Gerando um ponteiro para o nó tio para uma mais fácil visualização
                if (tio && tio->cor == RED) // Caso 1 -> tio == RED
                {
                    trocaCor(vo); // troca a cor do avo, do pai e do tio
                    no = vo; // no recebe seu avo
                }
                else
                {
                    if (no == pai->esq) // Caso 2 -> tio == preto (formato de joelho ou triiangular)
                    {
                        no = pai; // no recebe seu pai
                        rotacaoDireita(arvore, no); // Rotação a direita passando "no" (que agora é o seu pai)
                    }

                    // perceba que não tem um "else" aqui, ou seja, o caso 2 pressupõe o caso 3

                    no->nopai->cor = BLACK; // Caso 3 -> tio == preto (linha reta)
                    vo->cor = RED; // vo recebe a cor vermelha
                    rotacaoEsquerda(arvore, vo); // Rotação a esquerda passando "vo" (que agora é o seu pai)
                }
            }
        }

        arvore->raiz->cor = BLACK; // caso 0 -> o nó é a própria raiz
    }

    // transplantar: faz a parte de transplantar um nó a outro passado por parâmetro
    void transplantar(RBTree *arvore, No *u, No *v) // sabendo que "u" é o nó que será substituído pelo "v", segue a função:
    {
        if (u->nopai == NULL) { // se o pai do ó a ser transplantado for nulo, v é a nova raiz
            arvore->raiz = v;
        } else if (u == u->nopai->esq) { // se o nó a ser transplantado for filho esquerdo
            u->nopai->esq = v;
        } else { // se o nó a ser transplantado for filho direito
            u->nopai->dir = v;
        }

        if (v != NULL) { // se o nó a substituir o "u" (nó "v") não for nulo
            v->nopai = u->nopai;
        }
    }

    // minimo_direita: procura o minimo de um nó que está na direita, o que essa função faz é simplesmente ir ao máximo a esquerda possível, a fim de encontrar o nó mais próximo do nó pai
    No *minimo_direita(No *x)
    {
        while (x->esq != NULL) // Enquanto o nó da esquerda não for nulo, vai para a esquerda
        {
            x = x->esq;
        }

        return x; // Retorna o nó mais próximo da esquerda
    }

    // procuraNo: procura um No com a informação "dados.idade" identica a passada por "idade_chave"
    No *procuraNo(No *root, int idade_chave) // Pesquisa por um nó com a idade "idade_chave"
    {
        No *x = root; // x recebe a raiz
        while (x != NULL && idade_chave != x->dados.idade) // Enquanto o nó não for nulo e a idade do nó não for igual a "idade_chave", vai para a esquerda ou direita a depender da idade
        {
            if (idade_chave < x->dados.idade) {
                x = x->esq;
            } else {
                x = x->dir;
            }
        }

        return x;
    }

    // remocao: faz toda a parte de remoção, chamando as funções auxiliares
    void remocao(RBTree *arvore, int idade_chave) // Função principal da remoção, recebe a idade da pessoa a ser removida
    {
        No *z = procuraNo(arvore->raiz, idade_chave); // Procura o nó com a idade "idade_chave"

        if (z == NULL) { // Se o nó não for encontrado, ou seja, se for nulo, imprime "Chave não encontrada!"
            printf("Chave não encontrada!\n");
            return; // Retorna
        }

        No *y = z; // y recebe o nó "z"
        int y_orig_color = y->cor; // y_orig_color recebe a cor do nó "y"

        No *x;

        if (z->esq == NULL) { // Se o nó "z" não tiver filho esquerdo, então "x" recebe o filho direito de "z"
            x = z->dir; // x recebe o filho direito de "z" para o balanceamento
            transplantar(arvore, z, z->dir); // Transplanta o nó "z" pelo filho direito dele, conectando o pai ao seu neto (filho do nó "z")
        } else if (z->dir == NULL) { // Se o nó "z" não tiver filho direito, então "x" recebe o filho esquerdo de "z"
            x = z->esq; // x recebe o filho esquerdo de "z" para o balanceamento
            transplantar(arvore, z, z->esq); // Transplanta o nó "z" pelo filho esquerdo dele, conectando o pai ao seu neto (filho do nó "z")
        } else { // Se o nó "z" tiver ambos os filhos, então "y" recebe o mínimo do lado direito de "z"
            y = minimo_direita(z->dir); // y recebe o mínimo do lado direito de "z"
            y_orig_color = y->cor; // y_orig_color recebe a cor do nó "y"
            x = y->dir; // x recebe o filho direito de "y"
            if (x == NULL) { // Se o "x" (filho direito de "y") for nulo, então é feito um "mini-balanceamento", afim de corrigir o x, e não passar um x nulo para o balanceamento, o que ocasionaria muitos problemas, uma vez que ao entrarmos no balanceamento o ponteiro que x aponta não existiria, então não conseguiriamos chegar ao seu pai nem ao seu irmão
                y->nopai->dir->cor = RED; // irmão de y recebe a cor vermelha
                x = y->nopai; // x recebe o pai de y
            }
            if (y->nopai == z) { // Se o pai de "y" for o nó "z", então:
                if(x != NULL) // Se o "x" não for nulo, então (muito importante essa verificação, pois pode ser que o "x" seja nulo))
                    x->nopai = y; //o pai de "x" recebe "y"
            } else {
                transplantar(arvore, y, y->dir); // Transplanta o nó "y" pelo filho direito dele, conectando o pai ao neto direito dele (filho do nó "y")
                y->dir = z->dir; // filho direito de y recebe o filho direito de "z"
                y->dir->nopai = y; // o pai do filho direito de y recebe y como seu pai
            }

            transplantar(arvore, z, y); // Transplanta o nó "z" pelo nó "y"
            y->esq = z->esq; // filho esquerdo de y recebe o filho esquerdo de "z"
            y->esq->nopai = y; // o pai do filho esquerdo de y recebe y como seu pai
            y->cor = z->cor; // a cor de "y" recebe a cor de "z"
        }
        if (y_orig_color == BLACK) { // Se a cor do nó "y" for preto, então o balanceamento é executado
            balanceamento_remocao(arvore, x); // Executa o balanceamento
        }
        free(z); // Libera o nó "z"
    }

    // balanceamento_remocao: faz o balanceamento para o caso de uma remoção
    void balanceamento_remocao(RBTree *arvore, No *x) // Função de balanceamento, recebe o nó "x"
    {
        if(x != NULL)
        {
            while (x != arvore->raiz && x->cor == BLACK) // Enquanto o nó "x" não for a raiz e a cor dele for preto, o loop continua
            {
                if (x == x->nopai->esq) {
                    No *w = x->nopai->dir; // w recebe o irmão direito de x (pois "x" é filho esquerdo)

                    // Caso 1 -> w é vermelho
                    if (w->cor == RED) {
                        w->cor = BLACK; // w recebe preto
                        x->nopai->cor = RED; // pai de x recebe vermelho
                        rotacaoEsquerda(arvore, x->nopai); // rotação esquerda de x->pai
                        w = x->nopai->dir; // w recebe o filho direito de x->pai
                    }

                    // Caso 2 -> w é preto e os filhos de w são pretos
                    if (w->esq->cor == BLACK && w->dir->cor == BLACK) {
                        w->cor = RED; // w recebe vermelho
                        x = x->nopai; // x recebe o pai de x
                    } else {
                        // Caso 3 -> w é preto e o filho da esquerda é vermelho, e o filho da direita é preto
                        if (w->dir->cor == BLACK) {
                            w->esq->cor = BLACK; // filho da esquerda de w recebe com preta
                            w->cor = RED; // w recebe cor vermelha
                            rotacaoDireita(arvore, w); // rotação direita passando w
                            w = x->nopai->dir; // w recebe o filho direito de x->pai
                        }
                        // perceba que não há um "else", ou seja, o caso 3 pressupõe o caso 4

                        // Caso 4 -> w é preto e o filho da direita é vermelho
                        w->cor = x->nopai->cor; // w recebe a cor do pai de x
                        x->nopai->cor = BLACK; // pai de x recebe cor preta
                        w->dir->cor = BLACK; // filho da direita de w recebe cor preta
                        rotacaoEsquerda(arvore, x->nopai); // rotação esquerda passando x->pai
                        x = arvore->raiz; // x recebe a raiz
                    }
                } else {
                    No *w = x->nopai->esq; // w recebe o irmão esquerdo de x (pois "x" é filho direito)

                    // Caso 1 -> w é vermelho
                    if (w->cor == RED) {
                        w->cor = BLACK; // w recebe preto
                        x->nopai->cor = RED; // pai de x recebe vermelho
                        rotacaoDireita(arvore, x->nopai); // rotação direita de x->pai
                        w = x->nopai->esq; // w recebe o filho esquerdo de x->pai
                    }

                    // Caso 2 -> w é preto e os filhos de w são pretos
                    if (w->dir->cor == BLACK && w->esq->cor == BLACK) {
                        w->cor = RED; // w recebe vermelho
                        x = x->nopai; // x recebe o pai de x
                    } else {
                        // Caso 3 -> w é preto e o filho da direita é vermelho, e o filho da esquerda é preto
                        if (w->esq->cor == BLACK) {
                            w->dir->cor = BLACK; // filho da direita de w recebe com preta
                            w->cor = RED; // w recebe cor vermelha
                            rotacaoEsquerda(arvore, w); // rotação esquerda passando w
                            w = x->nopai->esq; // w recebe o filho esquerdo de x->pai
                        }

                        // perceba que não há um "else", ou seja, o caso 3 pressupõe o caso 4

                        // Caso 4 -> w é preto e o filho da direita é vermelho
                        w->cor = x->nopai->cor; // w recebe a cor do pai de x
                        x->nopai->cor = BLACK; // pai de x recebe cor preta
                        w->esq->cor = BLACK; // filho da esquerda de w recebe cor preta
                        rotacaoDireita(arvore, x->nopai); // rotação direita passando x->pai
                        x = arvore->raiz; // x recebe a raiz
                    }
                }
            }

            x->cor = BLACK; // Ao final, a cor do nó "x" é preto
        }
    }

    // Fazer o "printInOrder", basicamente imprime do menor elemento ao maior imprimindo tudo na esquerda para então imprimir tudo à direita por chamadas recursivas
    void printInOrder(No *no)
    {
        if (no == NULL)
            return;

        printInOrder (no->esq); // <- chamada recursiva
        printf("Nome: %s\nIdade: %d\n", no->dados.nome, no->dados.idade);
        printInOrder (no->dir); // <- chamada recursiva
    }


    void printSpaces(int n) // Função auxiliar para imprimir os espaços necessários
    {
        for (int i = 0; i < n; i++) { //n = numero de espaços
            printf(" "); //print espaço
        }
    }



    void printNo(No *no) // Função auxiliar para imprimir um nó da árvore
    {
        char color[10];
        strcpy(color, cor(no));
        if (no != NULL) {
            printf("%d (%s)", no->dados.idade, color);
        } else {
            printf("NULL");
        }
    }


    void printArvore(No *no, int space) // Imprimindo a árvore de uma forma mais visual
    {
        if (no == NULL) {
            printSpaces(space + 6);
            printf("NIL\n");
            return;
        }

        // Aumenta a distância entre os níveis
        space += 5;

        // Processa o nó da árvore da direita primeiro
        printArvore(no->dir, space + 4);

        printSpaces(space);
        printNo(no);
        printf("\n");


        // Processa o nó da árvore da esquerda
        printArvore(no->esq, space + 4);
    }


    char* cor(No *no) // Verifica a cor e retorna uma string, sendo "RED" para vermelho e "BLK" para preto, caso o nó seja "NULL" retorna "0"
    {
        if(no == NULL)
            return 0;

        char *r = "RED";
        char *b = "BLK";

        if(no->cor == 1)
            return r;
        else
            return b;
    }

    // Inverte a cor de um nó e seus filhos
    void trocaCor(No *no)
    {
        no->cor = !no->cor;
        if(no->dir != NULL)
            no->dir->cor = !no->dir->cor;
        if(no->esq != NULL)
            no->esq->cor = !no->esq->cor;
    }
