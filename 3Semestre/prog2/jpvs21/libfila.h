
#ifndef fila_h
#define fila_h

struct nodo_f {
    char letra;
    struct nodo_f *prox; 
    int *chaves;
    int tamanho;
};
typedef struct nodo_f nodo_f_t;

struct fila {
    nodo_f_t *ini;        
    nodo_f_t *fim;       
    int tamanho;     
};
typedef struct fila fila_t;

// retorna um ponteiro para a estrutura fila
fila_t * cria_fila ();

// destroia a fila e libera toda a memoria utilizada pela estrutura
fila_t * destroi_fila (fila_t *f);

// verifica se a fila esta vazia, retorna 1 caso esteja e 0 caso contrario
int fila_vazia(fila_t *f);

// retorna um inteiro que representa o tamanho da fila
int tamanho_fila (fila_t *f);

// verifica a existencia do char c na fila. Caso ja exista insere a chave no nodo de letra c, caso contrario cria um novo nodo com a letra c e insere a chave
// retorna 1 se a insercao foi bem sucedida e 0 em caso de falha
int insere_fila (fila_t *f, char c, int chave);

// busca um nodo de letra c na estrutura fila e retorna um ponteiro para ele
nodo_f_t *busca_fila (fila_t *f, char c);




#endif