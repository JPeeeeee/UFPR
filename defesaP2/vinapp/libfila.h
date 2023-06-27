
#ifndef fila_h
#define fila_h

#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

struct nodo_f {
    char *nome;
    char *path;
    uid_t UID;
    gid_t group;
    time_t dataAlteracao;
    int posicao;
    off_t tam;
    int b_ini;
    int b_fim;
    mode_t permissoes;
    struct nodo_f *prox;
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

// verifica se a fila esta vazia, retorna 1 caso esteja e 0 caso contrario
int fila_vazia(fila_t *f);

// retorna um inteiro que representa o tamanho da fila
int tamanho_fila (fila_t *f);

// retorna 1 se a insercao foi bem sucedida e 0 em caso de falha
int insere_fila (fila_t *f, char *name, FILE *arqBackup, struct stat info);

// retorna 1 se a insercao foi bem sucedida e 0 em caso de falha
// diferente da funcao anterior, esta recebe um nodo pronto como parametro
int insere_nodo_fila(fila_t *f, nodo_f_t *novo);

// remove um nodo da fila
void remove_fila (fila_t *f, nodo_f_t *removido);

// busca um nodo de letra c na estrutura fila e retorna um ponteiro para ele
nodo_f_t *busca_fila (fila_t *f, char *name);




#endif
