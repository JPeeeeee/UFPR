#include <stdlib.h>
#include "libfila.h"

fila_t* fila_cria (int max_elementos)
{
    fila_t *fila = (fila_t *) malloc(sizeof(fila_t));
    
    if (fila == NULL)
        return NULL;

    fila->elementos = (int*)malloc(sizeof(int) * max_elementos);
    if (fila->elementos == NULL){
        free(fila);
        return NULL;
    }

    fila->cabeca = 1;
    fila->cauda = 1;

    return fila;
}   

int cheia(fila_t* f)
{
    if ((f->cabeca == 1 && f->cauda == f->tamanho_max) || (f->cabeca == f->cauda + 1))
        return 1;
    return 0;
}

int queue (fila_t* f, int elemento)
{
    if (cheia(f)){
        if (f->cabeca == f->tamanho_max)
            f->cabeca = 1;
        return 0;
    }

    if (f->cauda >= f->tamanho_max + 1)
        f->cauda = 1;
    f->elementos[f->cauda] = elemento;
    f->cauda++;
    return 1;
}

int dequeue (fila_t* f, int* elemento)
{
    if (fila_vazia(f))
        return 0;
    
    *elemento = f->elementos[f->cabeca];
    if (f->cabeca == f->tamanho_max)
        f->cabeca = 1;
    else    
        f->cabeca++;

    return 1;
}

int fila_tamanho (fila_t* f)
{
    int tam;

    if (f->cabeca == f->cauda)
        tam = 0;
    else if (f->cauda > f->cabeca)
        tam = f->cauda - f->cabeca;
    else    
        tam = (f->cauda + f->cabeca) % f->tamanho_max;

    return tam;
}

int fila_vazia (fila_t* f)
{
    if (f->cabeca == f->cauda)
        return 1;
    return 0;
}

fila_t* fila_destroi (fila_t* f)
{
    free(f->elementos);
    free(f);
    
    return NULL;
}
