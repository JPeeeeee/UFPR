#include <stdlib.h>
#include "libfila.h"

fila_t* fila_cria ()
{
    fila_t *fila = malloc(sizeof(fila_t));
    if (fila == NULL)
        return NULL;

    fila->cabeca = NULL;
    fila->cauda = NULL;

    return fila;
}

int queue (fila_t* f, int elemento)
{
    nodo_f_t *novo = malloc(sizeof(nodo_f_t));
    
    if (novo == NULL)
        return 0;
    
    novo->chave = elemento;
    novo->prox = NULL;

    if (fila_vazia(f)){
        f->cabeca = novo;
        f->cauda = novo;
        f->tamanho++;
        return 1;
    } else{
        nodo_f_t *aux;
        aux = f->cauda;
        f->cauda = novo;
        aux->prox = f->cauda;
        f->tamanho++;
        return 1;
    }
}

int dequeue (fila_t* f, int* elemento)
{    
    if (fila_tamanho(f) == 1)
        f->cauda = NULL;

    if (!fila_vazia(f)){    
        *elemento = f->cabeca->chave;
        nodo_f_t *aux = f->cabeca;
        f->cabeca = f->cabeca->prox;
        free(aux);
        f->tamanho--;
        return 1;
    }
    return 0;
}

int fila_tamanho (fila_t* f)
{
    return f->tamanho;
}

int fila_vazia (fila_t* f)
{
    if (f->cabeca == NULL && f->cauda == NULL && f->tamanho == 0)
        return 1;
    return 0;
}

fila_t* fila_destroi (fila_t* f)
{
    int elemento;
    while(f->tamanho > 0)
        dequeue(f, &elemento);
    free(f);
    return NULL;
}
