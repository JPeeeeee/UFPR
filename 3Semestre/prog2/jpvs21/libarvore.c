#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include "libarvore.h"

void remove_arvore(nodo_t * raiz) {
    if (raiz == NULL)
        return;
    if (raiz->esq != NULL)
        remove_arvore(raiz->esq);
    if (raiz->dir != NULL)
        remove_arvore(raiz->dir);
    free(raiz);
}

void le_arvore(nodo_t *raiz) {
    printf("oi\n");
    if (raiz == NULL)
        return;
    le_arvore(raiz->esq);
    if (raiz->pai == NULL)
        printf("Chave: %d\nCor (0 = red, 1 = black): %d\nLetra: %lc\nRaiz\n\n", raiz->chave, raiz->cor, raiz->letra);
    else
        printf("Chave: %d\nCor (0 = red, 1 = black): %d\nLetra: %lc\nPai: %d\n\n", raiz->chave, raiz->cor,raiz->letra, raiz->pai->chave);
    le_arvore(raiz->dir);
}

nodo_t *cria_nodo() {
    nodo_t *novo = malloc(sizeof(nodo_t));

    if (novo == NULL)
        return NULL;

    novo->cor = RED;
    novo->dir = NULL;
    novo->esq = NULL;
    novo->pai = NULL;

    return novo;
}

void rotacao_dir_rb(nodo_t *p){
    printf("ROT DIR\n");
    nodo_t *aux = p->esq;
    aux->pai = p->pai; 
    if(aux->pai != NULL){
        if(aux->pai->esq == p)
            aux->pai->esq= aux;
        else    
            aux->pai->dir = aux;
    }
    p->esq = aux->dir;
    if(p->esq != NULL)
        p->esq->pai = p;

    aux->dir = p;
    p->pai = aux;
}

void rotacao_esq_rb(nodo_t *p){
    printf("ROT ESQ\n");
    nodo_t *aux = p->dir;
    aux->pai = p->pai;
    if(aux->pai != NULL) {
        if(aux->pai->dir == p)
            aux->pai->dir= aux;
        else    
            aux->pai->esq = aux;
    }

    p->dir = aux->esq;
    if(p->dir!=NULL)
        p->dir->pai = p;

    aux->esq = p;
    p->pai = aux;
}

void arruma_rb(nodo_t *raiz, nodo_t *no){

    nodo_t *tio = NULL;
    nodo_t *avo = NULL;

    //Enquanto o pai do no problematico for vermelho
    while (no->pai != NULL && no->pai->cor == RED) { 
        // o Pai eh filho da esquerda
        avo = no->pai->pai;
        if (no->pai == avo->esq) {
            tio = avo->dir;
            // Pai eh filho da esquerda com tio vermelho
            if (tio != NULL && tio->cor == RED){
                // Caso 1: Recolorir pai, tio e Avo
                no->pai->cor = BLACK;
                tio->cor = BLACK;
                avo->cor = RED;
                no = avo;
            } else {
                // no problematico eh filho da direita
                if (no == no->pai->dir) {
                    rotacao_esq_rb(no->pai);
                    no = no->esq;
                    avo = no->pai->pai;
                }
                rotacao_dir_rb(avo);
                no->pai->cor = BLACK; 
                avo->cor = RED;

                if (no->pai->pai != NULL)
                    arruma_rb(raiz, no->pai->pai);
                else
                    raiz = no->pai;
            }
        // Se o pai for filho da direita
        } else {
            avo = no->pai->pai;
            if (no->pai == avo->dir) {
                tio = avo->esq;
                // Pai eh filho da esquerda com tio vermelho
                if (tio != NULL && tio->cor == RED){
                    // Caso 1: Recolorir pai, tio e Avo
                    no->pai->cor = BLACK;
                    tio->cor = BLACK;
                    avo->cor = RED;
                    no = avo;
                } else {
                    // no problematico eh filho da direita
                    if (no == no->pai->esq) {
                        rotacao_dir_rb(no->pai);
                        no = no->dir;
                        avo = no->pai->pai;
                    }
                    rotacao_esq_rb(avo);
                    no->pai->cor = BLACK; 
                    avo->cor = RED;

                    if (no->pai->pai != NULL){
                        arruma_rb(raiz, no->pai->pai);

                    }
                    else{
                        printf("BO aqui\n");
                        raiz = no->pai;
                    }
                }
            }
        }
        raiz->cor = BLACK;
    }
}
//Cria um nó com os valores passados e inclui na arvore
nodo_t *inclui_rb(nodo_t *raiz, wchar_t letra, int chave){
   
    if(raiz == NULL){      
        raiz = cria_nodo();  
         //inclui na raiz
        if(raiz == NULL)
            return 0;
        raiz->chave = chave;
        raiz->letra = letra;
        raiz->cor = BLACK;
        return raiz;     
    }

    nodo_t *aux = raiz;
    nodo_t *pai;
    nodo_t *novoNo;

    while (aux != NULL){
        pai = aux;
        if (chave < aux->chave)
            aux = aux->esq;
        else
            aux = aux->dir;
    }
    novoNo = cria_nodo();
    novoNo->chave = chave;
    novoNo->letra = letra;

    if(novoNo == NULL)
        return NULL;

    if (chave < pai->chave)
        pai->esq = novoNo;
    else
        pai->dir =novoNo;

    novoNo->pai = pai;
    arruma_rb(raiz, novoNo);
    
    return novoNo;
}