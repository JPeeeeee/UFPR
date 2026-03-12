// PingPongOS - PingPong Operating System
// Prof. Carlos A. Maziero, DINF UFPR
// Versão 2.0 -- Junho de 2025

// Implementação do TAD fila genérica

#include "queue.h"
#include <stdlib.h>
#include <stdio.h>

struct nodo {
    struct nodo *proximo;
    void *item;
}; typedef struct nodo nodo_t;

struct queue_t {
    nodo_t *head;
    nodo_t *tail;
    nodo_t *iterador;
};

struct queue_t *queue_create() {
    struct queue_t *queue = malloc(sizeof(struct queue_t));

    if (!queue) 
        return NULL;

    queue->head = NULL;
    queue->tail = NULL;
    queue->iterador = NULL;

    return queue;
}

int queue_destroy(struct queue_t *queue) {
    if (queue) { 
        queue->iterador = queue->head;
        while (queue->iterador != NULL) {
            nodo_t *aux = queue->iterador;
            queue->iterador = queue->iterador->proximo;
            free(aux);
        }
        free(queue->iterador);
        free(queue);
        return NOERROR;
    }
    return ERROR;
}

int queue_add(struct queue_t *queue, void *item) {

    if (!queue)
        return ERROR;

    nodo_t *novo = malloc(sizeof(nodo_t));
    novo->item = item;

    if (!novo)
        return ERROR;

    if (!queue->head) {
        queue->head = novo;
        queue->tail = novo;
        queue->iterador = novo;
        return NOERROR;
    }

    queue->tail->proximo = novo;
    queue->tail = novo;
    queue->iterador = novo;
    return NOERROR;
}

int queue_del(struct queue_t *queue, void *item) {

    if (!queue)
        return ERROR;

    if (queue_size(queue) == 0) 
        return ERROR;

    nodo_t *aux1 = queue->head;
    nodo_t *aux2 = queue->head;

    // Verificar se a fila tem apenas um elemento
    if (aux1->item == item) {                
        if (!aux1->proximo) {
            queue->iterador = NULL;
        } else {
            queue->iterador = aux1->proximo;
        }
        queue->head = aux1->proximo;
        free(aux1);
        return NOERROR;
    }

    // Se a fila tem 2 ou mais elementos
    while (aux1->proximo != NULL) {
        if (aux1->item == item) {

            // Caso o iterador esteja apontado para o item a ser deletado
            if (queue->iterador == aux1) {
                if (!aux1->proximo) {
                    queue->iterador = NULL;
                } else {
                    queue->iterador = aux1->proximo;
                }
            }
            aux2->proximo = aux1->proximo;
            free(aux1);
            return NOERROR;
        }

        aux2 = aux1;
        aux1 = aux1->proximo;
    }
    
    // Deleta se for o ultimo e reajusta tail
    if (aux1->item == item) {
        if (queue->iterador == queue->tail)
            queue->iterador = NULL;
        queue->tail = aux2;
        queue->tail->proximo = NULL;
        free(aux1);
        return NOERROR;
    }

    return ERROR;
}

bool queue_has(struct queue_t *queue, void *item) {
    nodo_t *aux = queue->head;

    while (aux != NULL) {
        if (aux->item == item) 
            return true;
        aux = aux->proximo;
    }

    return false;
}

int queue_size(struct queue_t *queue) {
    int size = 0;
    
    if (!queue)
        return ERROR;

    if (!queue->head)
        return size;

    nodo_t *aux = queue->head;

    while (aux->proximo != NULL) {
        size += 1;
        aux = aux->proximo;
    }

    return size + 1;
}

void *queue_head(struct queue_t *queue) {
    if (!queue)
        return NULL;
    if (!queue->head)
        return NULL;

    queue->iterador = queue->head;
    return queue->iterador->item;
}

void *queue_next(struct queue_t *queue) {
    if (!queue)
        return NULL;

    if (queue->iterador == queue->tail) {
        queue->iterador = NULL;
        return NULL;
    }

    queue->iterador = queue->iterador->proximo;
    return queue->iterador->item;
}

void *queue_item(struct queue_t *queue) {
    if (!queue)
        return NULL;
    if (!queue->head)
        return NULL;

    return queue->iterador == NULL ? NULL : queue->iterador->item;
}

void queue_print(char *name, struct queue_t *queue, void(func)(void *)) {
    int countItems = 0;

    if (!queue) {
        printf("%s: undef\n", name);
        return;
    }

    printf("%s: [", name);

    nodo_t *aux = queue->head;

    if (!aux) {
        printf(" ] (%d items)\n", countItems);
        return;
    }

    while (aux->proximo != NULL) {
        printf(" ");

        if (!func) 
            printf("undef");
        else 
            func(aux->item);

        countItems += 1;
        aux = aux->proximo;
    }

    printf(" ");

    if (!func)
        printf("undef");
    else
        func(aux->item);

    printf(" ] (%d items)\n", countItems + 1);
}
