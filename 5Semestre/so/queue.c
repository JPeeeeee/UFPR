// Colocar comentário com nome aqui 

#include "queue.h"
#include <stdio.h>

int queue_size (queue_t *queue) {
    queue_t *head = queue;
    queue_t *queuePtr = queue;
    int count = 1;

    if (queue == NULL){
        return 0;
    }

    if (queuePtr->next == queuePtr) {
        return 1;
    }

    while (queuePtr->next != head) {
        queuePtr = queuePtr->next;
        count++;
    }

    return count;
}

void queue_print (char *name, queue_t *queue, void print_elem (void*) ) {
    printf("%s ", name);
    
    queue_t *head = queue;
    queue_t *queuePtr = queue;

    printf("[");
    
    if (queue != NULL)
        while (queuePtr->next != head) {
            print_elem(queuePtr);
            printf(" ");
            queuePtr = queuePtr->next;
        }
    
    print_elem(queuePtr);
    
    printf("]\n");
}

int queue_append (queue_t **queue, queue_t *elem) {

    if (elem->next != NULL || elem->prev != NULL)
    {
        return -1;
    }

    if (queue_size((*queue)) == 0) {
        (*queue) = elem;
        elem->next = elem;
        elem->prev = elem;
    }  else {
        queue_t *head = *queue;
        queue_t *ptrAux = *queue;

        while(ptrAux->next != head) {
            ptrAux = ptrAux->next;
        }

        elem->next = ptrAux->next;
        ptrAux->next = elem;
        elem->next->prev = elem;
        elem->prev = ptrAux;
    }

    return 0;
}

int queue_remove (queue_t **queue, queue_t *elem) {

    if (*queue == NULL){
        printf("A fila nao existe.\n");
        return -1;
    }

    if (queue_size(*queue) == 0) {
        printf("A fila esta vazia.\n");
        return -1;
    }

    if (elem->next == NULL || elem->prev == NULL) {
        return -1;
    }

    queue_t *head = *queue;
    queue_t *aux = *queue;

    while (aux->next != head) {

        if (aux == elem) {
            if (aux == head) {
                *queue = aux->next;
            }

            aux->next->prev = aux->prev;
            aux->prev->next = aux->next;

            aux->next = NULL;
            aux->prev = NULL;

            return 0;
        }

        aux = aux->next;

    }

    if ((*queue == (*queue)->next) && (*queue == elem)) {
        elem->next = NULL;
        elem->prev = NULL;
        *queue = NULL;

    } else if ((aux->next == head) && (aux == elem)) {
        aux->next->prev = aux->prev;
        aux->prev->next = aux->next;

        aux->next = NULL;
        aux->prev = NULL;
    } else {
        return -1;
    }

    return 0;

}
