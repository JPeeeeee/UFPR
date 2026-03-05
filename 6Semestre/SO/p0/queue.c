// PingPongOS - PingPong Operating System
// Prof. Carlos A. Maziero, DINF UFPR
// Versão 2.0 -- Junho de 2025

// Implementação do TAD fila genérica

#include "queue.h"
#include <stdlib.h>

struct nodo {
    struct nodo *proximo;
    void *data;
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

    queue->head = malloc(sizeof(nodo_t));
    queue->tail = malloc(sizeof(nodo_t));
    queue->iterador = malloc(sizeof(nodo_t));

    if (!queue->head || !queue->tail | !queue->iterador)
        return NULL;

    return queue;
}

int queue_destroy(struct queue_t *queue) {
    if (queue) 
        queue->iterador = queue->head;
        while (queue->iterador != NULL) {
            nodo_t *aux = queue->iterador;
            queue->iterador = queue->iterador->proximo;
            free(aux);
        }
        free(queue->iterador);
        free(queue);
        return NOERROR;
    return ERROR;
}

int queue_add(struct queue_t *queue, void *item) {

    if (!queue->head) {
        queue->head = item;
        queue->tail = item;
        queue->iterador = item;
        return NOERROR;
    }

    nodo_t *novo = malloc(sizeof(nodo_t));
    novo->data = item;

    if (!novo)
        return ERROR;

    queue->tail->proximo = novo;
    queue->tail = novo;
    return NOERROR;
}

