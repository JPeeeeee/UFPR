#include <stdlib.h>
#include <stdio.h>
#include "libfila.h"

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
    
    while (aux != NULL) {
        if (aux->letra == c)
            return aux;
        aux = aux->prox;
    }

    return NULL;
}

int adiciona_chave (fila_t *f, char c, int chave) {

    nodo_f_t *aux = f->ini;

    while (aux->letra != c) {
        aux = aux->prox;
    }

    if (aux->chaves == NULL){
        aux->chaves = malloc(sizeof(int));
        aux->chaves[0] = chave;
        aux->tamanho++;
        return 1;
    } else{
        aux->tamanho++;
        aux->chaves = realloc(aux->chaves, sizeof(int) * aux->tamanho);
        aux->chaves[aux->tamanho - 1] = chave;
        return 1;
    }
    return 0;
}

int insere_fila (fila_t* f, char c, int chave) {

    if (busca_fila(f, c)){
        adiciona_chave(f, c, chave);
        return 1;
    }

    nodo_f_t *novo = malloc(sizeof(nodo_f_t));
    
    if (novo == NULL)
        return 0;
    
    novo->letra = c;
    novo->prox = NULL;
    novo->chaves = malloc(sizeof(int));
    novo->chaves[0] = chave;
    novo->tamanho = 1;

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

char retira_fila (fila_t* f) {    

    char elemento;

    if (tamanho_fila(f) == 1){
        elemento = f->fim->letra;
        free(f->fim->chaves);
        free(f->fim);
        f->tamanho--;
        return elemento;
    }

    if (!fila_vazia(f)){    
        nodo_f_t *aux = f->ini;
        elemento = aux->letra;
        f->ini = f->ini->prox;
        free(aux->chaves);
        free(aux);
        f->tamanho--;
        return elemento;
    }
    return -1;
}


int tamanho_fila (fila_t* f) {
    return f->tamanho;
}

int fila_vazia (fila_t* f) {

    if (f->ini == NULL && f->fim == NULL && f->tamanho == 0)
        return 1;

    return 0;
}

fila_t* destroi_fila (fila_t* f) {

    while(tamanho_fila(f) > 0)
        retira_fila(f);

    free(f);

    return NULL;
}