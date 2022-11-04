#include <stdlib.h>
#include "liblef.h"

lef_t * cria_lef (){
    lef_t *lef = malloc(sizeof(lef_t));
    if (lef == NULL)
        return 0;
    lef->Primeiro = NULL;
    return lef;
}

lef_t * destroi_lef (lef_t *l){
    nodo_lef_t *aux;
    while (l->Primeiro->prox != NULL){
        aux = l->Primeiro;
        l->Primeiro = l->Primeiro->prox;
        aux->evento->destroidados(aux->evento->dados);
        free(aux);
    }
    l->Primeiro->evento->destroidados(l->Primeiro->evento->dados);
    free(l->Primeiro);
    free(l);
    return NULL;
}

int adiciona_inicio_lef (lef_t *l, evento_t *evento){
    nodo_lef_t *novo = malloc(sizeof(nodo_lef_t));
    novo->evento = evento;
    novo->prox = l->Primeiro;
    l->Primeiro = novo;

    if (novo->prox == NULL || l->Primeiro == NULL)
        return 0;
    return 1;
}

int adiciona_ordem_lef  (lef_t *l, evento_t *evento){
    if (l->Primeiro == NULL){
        adiciona_inicio_lef(l, evento);
        return 0;
    } 

    nodo_lef_t *novo = malloc(sizeof(nodo_lef_t));
    nodo_lef_t *aux = malloc(sizeof(nodo_lef_t));
    novo->evento = evento;
    aux = l->Primeiro;
    
    while (aux->prox != NULL){
        if (evento->tempo < aux->evento->tempo){
            novo->prox = aux;
            l->Primeiro = novo;
            return 0;
        }
        if (evento->tempo < aux->prox->evento->tempo){
            novo->prox = aux->prox;
            aux->prox = novo;
            return 0;
        }
        aux = aux->prox;
    }
    aux->prox = novo;
    return 0;
}

int checa_lef (lef_t *l, int tipo){
    nodo_lef_t *aux = malloc(sizeof(nodo_lef_t));
    aux = l->Primeiro;
    while (aux->prox != NULL){
        if (aux->evento->tipo == tipo)
            return 1;
        aux = aux->prox;
    }
    return 0;
}

evento_t * obtem_primeiro_lef (lef_t *l){
    if (l->Primeiro == NULL)
        return NULL;
    nodo_lef_t *aux = malloc(sizeof(nodo_lef_t));
    aux = l->Primeiro;
    l->Primeiro = l->Primeiro->prox;
    return aux->evento;
}