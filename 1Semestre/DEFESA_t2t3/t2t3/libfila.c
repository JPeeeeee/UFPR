#include <stdlib.h>
#include "libfila.h"

fila_t* cria_fila ()
{
    fila_t *fila = malloc(sizeof(fila_t));
    if (fila == NULL)
        return NULL;

    fila->ini = NULL;
    fila->fim = NULL;

    return fila;
}

int insere_fila (fila_t* f, int elemento)
{
    nodo_f_t *novo = malloc(sizeof(nodo_f_t));
    
    if (novo == NULL)
        return 0;
    
    novo->chave = elemento;
    novo->prox = NULL;

    if (fila_vazia(f)){
        f->ini = novo;
        f->fim = novo;
        f->tamanho++;
        return 1;
    } else{
        nodo_f_t *aux;
        aux = f->fim;
        f->fim = novo;
        aux->prox = f->fim;
        f->tamanho++;
        return 1;
    }
}

int retira_fila (fila_t* f, int* elemento)
{    
    if (tamanho_fila(f) == 1)
        f->fim = NULL;

    if (!fila_vazia(f)){    
        *elemento = f->ini->chave;
        nodo_f_t *aux = f->ini;
        f->ini = f->ini->prox;
        free(aux);
        f->tamanho--;
        return *elemento;
    }
    return 0;
}

int tamanho_fila (fila_t* f)
{
    return f->tamanho;
}

int fila_vazia (fila_t* f)
{
    if (f->ini == NULL && f->fim == NULL && f->tamanho == 0)
        return 1;
    return 0;
}

fila_t* destroi_fila (fila_t* f)
{
    int elemento;
    while(f->tamanho > 0)
        retira_fila(f, &elemento);
    free(f);
    return NULL;
}
