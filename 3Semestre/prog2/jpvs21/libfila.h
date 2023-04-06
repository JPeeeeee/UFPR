
/*

 */
#ifndef fila_h
#define fila_h

struct nodo_f {
    char letra;          /* lista de numeros inteiros               */
    struct nodo_f *prox;  /* ponteiro para o proximo (obrigatorio)   */
    struct nodo_f *prev;  /* ponteiro para o anterior (uso opcional) */
    int *chaves;
    int tamanho;
};
typedef struct nodo_f nodo_f_t;

struct fila {
    nodo_f_t *ini;        /* ponteiro para o inicio da lista (obrigatorio)       */
    nodo_f_t *fim;        /* ponteiro para o fim da lista (uso opcional)         */
    int tamanho;        /* tamanho da lista (numero de elementos na lista)     */
};
typedef struct fila fila_t;

/*
 * Cria uma fila vazia e a retorna, se falhar retorna NULL.
 */
fila_t * cria_fila ();

/*
 * Remove todos os elementos da fila, libera espaco e devolve NULL.
 */
fila_t * destroi_fila (fila_t *f);

/*
 * Retorna 1 se a fila esta vazia e 0 caso contrario.
 */
int fila_vazia (fila_t *f);

/*
 * Retorna o tamanho da fila, isto eh, o numero de elementos presentes nela.
 */
int tamanho_fila (fila_t *f);

/*
 * Insere o elemento no final da fila (politica FIFO).
 * Retorna 1 se a operacao foi bem sucedida e 0 caso contrario.
 */
int insere_fila (fila_t *f, char c, int chave);


nodo_f_t *busca_fila (fila_t *f, char c);


/*
 * Remove o elemento do inicio da fila (politica FIFO) e o retorna.
 * Retorna 1 se a operacao foi bem sucedida e 0 caso contrario.
 */
char retira_fila (fila_t *f);


/*
 * As funcoes abaixo permitem quebrar a politica FIFO da fila,
 * Permite acesso a elementos apontados pelo ponteiro 'atual'.
 * Este ponteiro pode ser inicializado e incrementado, viabilizando
 * a implementacao de um mecanismo iterador.
 */

#endif