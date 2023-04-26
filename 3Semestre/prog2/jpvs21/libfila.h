
#ifndef fila_h
#define fila_h

struct nodo_f {
    char letra;
    struct nodo_f *prox; 
    struct nodo_f *prev; 
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

fila_t * cria_fila ();

fila_t * destroi_fila (fila_t *f);

int fila_vazia (fila_t *f);

int tamanho_fila (fila_t *f);

int insere_fila (fila_t *f, char c, int chave);

nodo_f_t *busca_fila (fila_t *f, char c);

char retira_fila (fila_t *f);

#endif