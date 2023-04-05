enum {
    RED, 
    BLACK
};

struct nodo {
    char letra;  
    int chave; 
    int cor;     /* lista de numeros inteiros               */
    struct nodo_f *esq;  /* ponteiro para o proximo (obrigatorio)   */
    struct nodo_f *dir;  /* ponteiro para o anterior (uso opcional) */
    struct nodo_f *pai;
};

typedef struct nodo nodo_t;

nodo_t *cria_nodo();

nodo_t *insere_valor(nodo_t *raiz, char letra, int chave);

nodo_t *busca_chave(nodo_t *raiz, int chave);

nodo_t *busca_letra(nodo_t *raiz, char letra);