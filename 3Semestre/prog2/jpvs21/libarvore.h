
/*

 */
#include <wchar.h>

enum Cor {
    RED,
    BLACK
};

struct nodo {
    int chave;
    enum Cor cor;
    wchar_t letra;
    struct nodo *esq;
    struct nodo *dir;
    struct nodo *pai;
};
typedef struct nodo nodo_t;

void le_arvore(nodo_t *raiz);

nodo_t *cria_nodo();

// nodo_t *busca_RB_chave(nodo_t *raiz, int chave);

// nodo_t *busca_RB_letra(nodo_t *raiz, char letra);

nodo_t *inclui_rb(nodo_t *raiz, wchar_t letra, int chave);

void remove_arvore(nodo_t *raiz);