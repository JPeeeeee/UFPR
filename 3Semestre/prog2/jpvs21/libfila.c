#include <stdlib.h>
#include <stdio.h>
#include "libfila.h"

// 
fila_t* cria_fila () {

    fila_t *fila = malloc(sizeof(fila_t));

    if (fila == NULL)
        return NULL;

    fila->ini = NULL;
    fila->fim = NULL;
    fila->tamanho = 0;

    return fila;
}

nodo_f_t *busca_fila (fila_t *f, char c) {

    nodo_f_t *aux = f->ini;
    
    // enquanto aux receber um nodo da fila, compara a letra de aux com a 
    // letra procurada e, caso sejam iguais, retorna um ponteiro para o nodo atual
    while (aux != NULL) {
        if (aux->letra == c)
            return aux;
        aux = aux->prox;
    }

    return NULL;
}

int adiciona_chave (fila_t *f, char c, int chave) {

    // aux recebe o nodo com letra 'char c'
    nodo_f_t *aux = busca_fila(f, c);

    if (aux == NULL)
        return 0;

    // o vetor de chaves de aux recebe um realloc de tamanho 
    aux->tamanho++;
    aux->chaves = realloc(aux->chaves, sizeof(int) * aux->tamanho);
    aux->chaves[aux->tamanho - 1] = chave;
    return 1;
}

int insere_fila (fila_t* f, char c, int chave) {

    // caso o valor ja exista na fila, chama a funcao adiciona_chave
    if (busca_fila(f, c)){
        adiciona_chave(f, c, chave);
        return 1;
    }

    nodo_f_t *novo = malloc(sizeof(nodo_f_t));
    
    if (novo == NULL)
        return 0;
    
    // inicializa os valores do novo nodo e aloca o tamanho de um unico 
    // valor int e insere a chave na primeira posicao do vetor
    novo->letra = c;
    novo->prox = NULL;
    novo->chaves = malloc(sizeof(int));
    novo->chaves[0] = chave;
    novo->tamanho = 1;

    // reajusta os ponteiros de inicio e fim da fila
    if (fila_vazia(f)){
        f->ini = novo;
        f->fim = novo;
        f->tamanho++;
        return 1;
    } else{
        nodo_f_t *aux = f->fim;
        f->fim = novo;
        aux->prox = f->fim;
        f->tamanho++;
        return 1;
    }
}


// funcao que retira o primeiro elemento da fila
void retira_fila (fila_t* f) {    

    // caso a fila possua apenas um elemento
    // retira o unico elemento presente
    if (tamanho_fila(f) == 1){
        free(f->fim->chaves);
        free(f->fim);
        f->tamanho--;
        return;
    }

    // retira o primeiro elemento da fila e reajusta o ponteiro de inicio da fila
    if (!fila_vazia(f)){    
        nodo_f_t *aux = f->ini;
        f->ini = f->ini->prox;
        free(aux->chaves);
        free(aux);
        f->tamanho--;
        return;
    }

    return;
}

// retorna um inteiro com o tamnaho da fila
int tamanho_fila (fila_t* f) {
    return f->tamanho;
}

// retorna 1 caso a fila esteja vazia e 0 caso contrario
int fila_vazia (fila_t* f) {

    if (f->ini == NULL && f->fim == NULL && f->tamanho == 0)
        return 1;

    return 0;
}


// desaloca cada nodo presente na fila e da free na estrutura
fila_t* destroi_fila (fila_t* f) {

    while(tamanho_fila(f) > 0)
        retira_fila(f);

    free(f);

    return NULL;
}