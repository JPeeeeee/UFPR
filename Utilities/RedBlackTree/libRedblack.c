#include <stdio.h>
#include <stdlib.h>
#include "libRedblack.h"

nodo_t *cria_nodo(int chave, int cor, char letra, nodo_t *raiz) {
    nodo_t *novo = malloc(sizeof(nodo_t));

    if (novo == NULL)
        return NULL;

    novo->cor = cor;
    novo->letra = letra;
    novo->chave = chave;
    novo->dir = NULL;
    novo->esq = NULL;
    novo->pai = raiz;

    return novo;
}

nodo_t *insere_valor(nodo_t *raiz, char letra, int chave) {
    nodo_t *tio = NULL, *noAsc;
    while ()
}

nodo_t *busca_chave(nodo_t *raiz, int chave) {
    if (raiz->chave == chave)
        return raiz;
    if (raiz->chave > chave)
        return busca_chave(raiz->esq, chave);
    else    
        return busca_chave(raiz->dir, chave);
}

nodo_t *busca_letra(nodo_t *raiz, char letra) {
    if (raiz->letra == letra)
        return raiz;
    if (raiz->letra > letra)
        return busca_letra(raiz->esq, letra);
    else    
        return busca_letra(raiz->dir, letra);
}