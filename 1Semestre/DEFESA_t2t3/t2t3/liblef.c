#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "liblef.h"

lef_t * cria_lef () {
    lef_t *lef;
    if ((lef = malloc (sizeof (lef_t)))) {
        lef->Primeiro = NULL;
        return lef;
    } else return NULL;
}

lef_t * destroi_lef (lef_t *l) {
    nodo_lef_t *nodo;
    if (l->Primeiro == NULL) {
        free (l);
        return NULL;
    }
    while (l->Primeiro != NULL) {
        nodo = l->Primeiro;
        l->Primeiro = l->Primeiro->prox;
        free (nodo->evento->dados);
        free (nodo->evento);
        free (nodo);
    }
    free (l);
    return NULL;
}

int adiciona_inicio_lef (lef_t *l, evento_t *evento) {
    nodo_lef_t *nodo;
    evento_t *evento_aux;
    if ((evento_aux = malloc (sizeof(evento_t)))) {
        evento_aux->tempo = evento->tempo;
        evento_aux->tipo = evento->tipo;
        evento_aux->tamanho = evento->tamanho;
        evento_aux->dados = malloc (evento->tamanho);
        memcpy (evento_aux->dados, evento->dados, evento->tamanho);
    } else return 0;

    if ((nodo = malloc (sizeof (nodo_lef_t)))) {
        nodo->evento = evento_aux; 
        nodo->prox = NULL;
    } else return 0;
    if (l->Primeiro == NULL) 
        l->Primeiro = nodo;
    else {
        nodo->prox = l->Primeiro;
        l->Primeiro = nodo;
    }
    return 1;
}

int adiciona_ordem_lef  (lef_t *l, evento_t *evento) {
    nodo_lef_t *nodo, *aux1, *aux2;
    evento_t *evento_aux = malloc (sizeof(evento_t));

    if (evento_aux == NULL){
        free(evento_aux);
        return 0;
    }

    evento_aux->tempo = evento->tempo;
    evento_aux->tipo = evento->tipo;
    evento_aux->tamanho = evento->tamanho;
    evento_aux->dados = malloc (evento->tamanho);
    memcpy (evento_aux->dados, evento->dados, evento->tamanho);

    nodo = malloc (sizeof (nodo_lef_t));
    if (nodo == NULL){
        free(evento_aux);
        return 0;
    }

    aux2 = l->Primeiro;

    if (aux2 == NULL) {
        free (evento_aux->dados);
        free (evento_aux);
        free (nodo);
        adiciona_inicio_lef (l, evento);

        return 1;
    }

    while (aux2->prox != NULL && aux2->evento->tempo < evento->tempo) {
        aux1 = aux2;
        aux2 = aux2->prox;
    }

    if (aux2 == l->Primeiro && aux2->evento->tempo >= evento->tempo) {
        free (evento_aux->dados); 
        free (evento_aux); 
        free (nodo); 
        adiciona_inicio_lef (l, evento);
        
        return 1;
    } else if (aux2->prox == NULL) {
        nodo->evento = evento_aux;
        aux2->prox = nodo;
        nodo->prox = NULL;
    } else { 
        nodo->evento = evento_aux; 
        aux1->prox = nodo; 
        nodo->prox = aux2;
    }

    return 1;
}

evento_t * obtem_primeiro_lef (lef_t *l) {
    nodo_lef_t *nodo;
    evento_t *evento;
    
    if (!l->Primeiro) return NULL;

    evento = l->Primeiro->evento; 
    nodo = l->Primeiro;

    l->Primeiro = l->Primeiro->prox;
    free (nodo);
    return evento;
}