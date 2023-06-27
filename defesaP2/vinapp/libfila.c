#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <limits.h>
#include "libfila.h"

#define MAXPATH 1024

// 
fila_t* cria_fila () {

    fila_t *fila = malloc(sizeof(fila_t));

    if (fila == NULL)
        return NULL;

    fila->ini = NULL;
    fila->fim = NULL;
    fila->tamanho = 0;

    return fila;
}

nodo_f_t *busca_fila (fila_t *f, char *name) {

    nodo_f_t *aux = f->ini;

    // enquanto aux receber um nodo da fila, compara a letra de aux com o 
    // nome procurado e, caso sejam iguais, retorna um ponteiro para o nodo atual
    while (aux != NULL) {    

        if (!strcmp(name, aux->nome)){
            return aux;
        }
        aux = aux->prox;
    }

    return NULL;
}

// retorna o tamanho de um arquivo
int tamArquivo(FILE *arqBackup) {
    struct stat info;
    fstat(fileno(arqBackup), &info);
    return info.st_size;
}

// insere um nodo ja criado dentro da fila
int insere_nodo_fila(fila_t *f, nodo_f_t *novo){
    if (fila_vazia(f)){
        f->ini = novo;
        f->fim = novo;
        f->tamanho++;
        return 1;
    } else{
        nodo_f_t *aux = f->fim;
        f->fim = novo;
        aux->prox = f->fim;
        f->tamanho++;
        return 1;
    }
}

int insere_fila (fila_t* f, char *name, FILE *arqBackup, struct stat info) {

    nodo_f_t *novo = malloc(sizeof(nodo_f_t));
    
    if (novo == NULL)
        return 0;
    
    // inicializa os valores do novo nodo e aloca o tamanho de um unico 
    // valor int e insere a chave na primeira posicao do vetor
    novo->prox = NULL;
    novo->nome = name;
    novo->path = name;

    // seta os valores de inicio para caso nao exista nenhum arquivo em backup
    if (f->fim){
        if (f->fim->b_fim == 0)
            novo->b_ini = f->fim->b_fim + 4;
        else 
            novo->b_ini = f->fim->b_fim + 1;
    }
    else {
        novo->b_ini = tamArquivo(arqBackup);
    }

    novo->b_fim = novo->b_ini + info.st_size - 1;
    novo->tam = info.st_size;
    novo->dataAlteracao = info.st_mtime;
    novo->permissoes = info.st_mode; 
    novo->UID = info.st_uid;
    novo->group = info.st_gid;
    novo->posicao = tamanho_fila(f) + 1;

    // reajusta os ponteiros de inicio e fim da fila
    if (f->tamanho == 0){
        f->ini = novo;
        f->fim = novo;
        f->tamanho++;

        return 1;
    } else{
        nodo_f_t *aux = f->fim;
        f->fim = novo;
        aux->prox = f->fim;
        f->tamanho++;

        return 1;
    }
}

// remove um nodo da fila (o nodo requerido deve ser passado como parametro)
// e reajusta os ponteiros da fila
void remove_fila (fila_t *f, nodo_f_t *removido) {
    nodo_f_t *aux = removido->prox;

    if (!(removido == f->ini)){
        nodo_f_t *anterior = f->ini;

        while(anterior->prox != removido) 
            anterior = anterior->prox;

        if (removido == f->fim) 
            f->fim = anterior;

        anterior->prox = aux;
    } else 
        f->ini = aux;
    f->tamanho -= 1;
}

// retorna um inteiro com o tamnaho da fila
int tamanho_fila (fila_t* f) {
    return f->tamanho;
}

// retorna 1 caso a fila esteja vazia e 0 caso contrario
int fila_vazia (fila_t* f) {

    if (f->ini == NULL && f->fim == NULL && f->tamanho == 0)
        return 1;

    return 0;
}

