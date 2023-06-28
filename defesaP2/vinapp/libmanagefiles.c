#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include "libmanagefiles.h"
#include "libfila.h"
#include "libutils.h"

#define BUFF 1024

void transcreveArquivo (FILE *arqBackup, char *arquivo, fila_t* diretorio) {
    char buffer[BUFF];
    struct stat info;
    int tamBackup = tamanhoArquivo(arqBackup);
    int tamArqLeitura, nLeituras, iniEscrita;

    FILE *arqTranscrever = fopen(arquivo, "r");
    if (!arqTranscrever)
        return;

    // leitura bufferizada
    stat(arquivo, &info);
    tamArqLeitura = info.st_size;
    nLeituras = tamArqLeitura / BUFF;

    if (tamBackup == 0) 
        fseek(arqBackup, tamBackup + sizeof(int), SEEK_SET);
    else {
        iniEscrita = diretorio->fim->b_fim + 1;
        fseek(arqBackup, iniEscrita, SEEK_SET);
    }

    // insere uma estrutura de dados com as informacoes do novo arquivo no diretorio
    insere_fila(diretorio, arquivo, arqBackup, info);


    for (int i = 0; i < nLeituras; i++){
        fread(buffer, 1, BUFF, arqTranscrever);
        fwrite(buffer, 1, BUFF, arqBackup);
    }

    if (tamArqLeitura % BUFF) {
        fread(buffer, 1, tamArqLeitura % BUFF, arqTranscrever);
        fwrite(buffer, 1, tamArqLeitura % BUFF, arqBackup);
    }

    rewind(arqBackup);
    fclose(arqTranscrever);
}



void inclusaoDeArquivo (FILE *arqBackup, char *nome, int optA, fila_t *diretorio) { 

    // verifica se o arquivo ja existe no backup

    nodo_f_t *nodoBuscado = busca_fila(diretorio, nome);

    // verifica se a opcao de atualizar foi selecionada
    if(optA) {

        // se o arquivo nao existe no backup, age como a funcao insere
        // caso contrario verifica se eh preciso atualizar
        if (!nodoBuscado) {
            transcreveArquivo(arqBackup, nome, diretorio);
            escreveDiretorio(diretorio, arqBackup);
            printf("Arquivo criado no backup!\n");
            rewind(arqBackup);
        } else {

            struct stat info;
            stat(nome, &info);

            if(info.st_mtime > nodoBuscado->dataAlteracao) {

                removeArquivo(nome, arqBackup, diretorio);
                transcreveArquivo(arqBackup, nome, diretorio);
                
                escreveDiretorio(diretorio, arqBackup);

                rewind(arqBackup);
            } else {
                printf("ATENCAO! '%s' ja esta na versao mais recente!\ntam diretorio: %d\n", nodoBuscado->nome, diretorio->tamanho);
            }
        }
    } else { // funcao insere normal

        if (!nodoBuscado) {
            transcreveArquivo(arqBackup, nome, diretorio); 
            escreveDiretorio(diretorio, arqBackup);
            printf("Arquivo inserido com sucesso!\n");
            // rodar com gdb watch f->ini do arquivo main    
        }
        else 
            printf("Arquivo ja se encontra no backup\n"); 
    }
}


/* REMOVE */

// funcao que reescreve o diretorio no fim do arquivo backup apos a remocao
void reescreveDiretorio (FILE *arqBackup, fila_t *f, char *nome) {
    // tira o nodo do arquivo da estrutura diretorio
    nodo_f_t *removido = busca_fila(f, nome);
    int posDiretorio, posNovoDiretorio;
    remove_fila(f, removido);

    // reescreve o novo diretorio
    fseek(arqBackup, 0, SEEK_SET);
    fread(&posDiretorio, sizeof(int), 1, arqBackup);

    posNovoDiretorio = posDiretorio - removido->tam;
    fseek(arqBackup, posNovoDiretorio, SEEK_SET);
    fwrite(&f->tamanho, sizeof(int), 1, arqBackup);

    free(removido);    

    lacoEscrita(f, arqBackup);

    fseek(arqBackup, 0, SEEK_SET);
    fwrite(&posNovoDiretorio, sizeof(int), 1, arqBackup);
}

void removeArquivo(char *nome, FILE *arqBackup, fila_t *f) {
    // verifica se o arquivo realmente existe no backup
    int comeco, fim;
    nodo_f_t *removido = busca_fila(f, nome);

    if (!removido) {
        printf("ERRO! Arquivo(s) inexistente(s)!\n");

        nodo_f_t *auxNome = f->ini;

        if (!auxNome)
            exit(1);

        printf("Arquivos no backup:\n");

        while (auxNome != NULL){
            printf("- %s\n", auxNome->nome);
            auxNome = auxNome->prox;
        }

        exit(1);
    }

    // se o arquivo removido for o unico em backup zera o conteudo do arquivo de backup
    if (f->tamanho == 1){
        ftruncate(fileno(arqBackup), 0);
        reescreveDiretorio(arqBackup, f, nome);
        return;
    }


    // remove o arquivo do backup
    comeco = removido->b_ini;
    fim = removido->b_fim;

    removeBytes(arqBackup, comeco, fim);

    nodo_f_t *aux = removido->prox;


    while(aux) {
        aux->posicao -= 1;
        aux->b_fim -= removido->tam;
        aux->b_ini -= removido->tam;
        aux = aux->prox;
    }

    reescreveDiretorio(arqBackup, f, nome);
    rewind(arqBackup);
}

/* EXTRAI */

void extraiArquivo(char *nome, FILE *arqBackup, fila_t *f) {
    rewind(arqBackup);
    char buffer[BUFF];
    int tamBackup = tamanhoArquivo(arqBackup);
    int tamArqLeitura, nLeituras, iniLeitura;

    nodo_f_t *extraido = busca_fila(f, nome);
    if (!extraido)
        return;

    tamArqLeitura = extraido->tam;

    // cria o arquivo no diretorio atual e seta as permissoes
    FILE *arqTranscrever = fopen(nome, "w");
    chmod(extraido->path, extraido->permissoes);
    printf("Arquivo extraido em: %s\n", nome);
    if (!arqTranscrever)
        return;

    // leitura bufferizada do arquivo
    nLeituras = tamArqLeitura / BUFF;

    if (tamBackup == 0) 
        return;
    else {
        iniLeitura = extraido->b_ini;
        fseek(arqBackup, iniLeitura, SEEK_SET);
    }

    for (int i = 0; i < nLeituras; i++){
        fread(buffer, 1, BUFF, arqBackup);
        fwrite(buffer, 1, BUFF, arqTranscrever);
    }

    if (tamArqLeitura % BUFF) {
        fread(buffer, sizeof(char), tamArqLeitura % BUFF, arqBackup);
        fwrite(buffer, sizeof(char), tamArqLeitura % BUFF, arqTranscrever);
    }

    rewind(arqBackup);

    fclose(arqTranscrever);
}

/* MOVER */

void moveArquivo(char *movido, char *anterior, FILE *arqBackup, fila_t *f) {
    nodo_f_t *nodoMovido = busca_fila(f, movido);
    nodo_f_t *nodoAnterior = busca_fila(f, anterior);

    if (!nodoMovido || !nodoAnterior)
        return;

    if (nodoMovido == nodoAnterior)
        return;

    if (nodoMovido == nodoAnterior->prox)
        return;

    // reajuste de posicao no diretorio
    remove_fila(f, nodoMovido);

    nodo_f_t *aux = nodoMovido->prox;

    while ((aux != nodoAnterior) && aux){
        aux->posicao--;
        aux = aux->prox;
    }

    nodoMovido->prox = nodoAnterior->prox;
    nodoMovido->posicao = nodoAnterior->posicao;
    nodoAnterior->prox = nodoMovido;
    nodoAnterior->posicao--;

    f->tamanho++;
    
    aux = f->ini;
    while (aux->prox != NULL)
        aux = aux->prox;
    f->fim = aux;

    // reescrita na posicao correta
    char buffer[BUFF];

    // abre espaco para arquivo movimentado
    int iniEspaco = nodoAnterior->b_fim + 1;
    int tamDadosposteriores = tamanhoArquivo(arqBackup) - iniEspaco;
    int rt, read;
    int controller = tamanhoArquivo(arqBackup);
    int tamArquivo = tamanhoArquivo(arqBackup);
    int newPos = nodoMovido->tam;

    if (tamDadosposteriores < BUFF)
        read = tamArquivo - tamDadosposteriores;
    else
        read = tamArquivo - BUFF;

    fseek(arqBackup, read, SEEK_SET);
      
    while (controller > iniEspaco) {
        if (tamDadosposteriores < BUFF) 
            rt = fread(&buffer, 1, tamDadosposteriores, arqBackup);
        else 
            rt = fread(&buffer, 1, BUFF, arqBackup);
        
        fseek(arqBackup, newPos + tamArquivo - (tamArquivo - nodoAnterior->b_fim - 1), SEEK_SET);
        fwrite(buffer, 1, rt, arqBackup);

        controller -= rt;
        newPos += rt;
        read -= rt;
        fseek(arqBackup, read, SEEK_SET);
    }

    // escreve o arquivo no lugar certo
    int nLeituras = nodoMovido->tam / BUFF;
    int posLeitura;

    if (nodoMovido->posicao > nodoAnterior->posicao)
        posLeitura = nodoMovido->b_ini;
    else
        posLeitura = nodoMovido->b_ini + nodoMovido->tam;

    int posEscrita = nodoAnterior->b_fim + 1;

    for (int i = 0; i < nLeituras; i++){
        fseek(arqBackup, posLeitura, SEEK_SET);
        rt = fread(buffer, 1, BUFF, arqBackup);
        fseek(arqBackup, posEscrita, SEEK_SET);
        fwrite(buffer, 1, BUFF, arqBackup);

        posLeitura += rt;
        posEscrita += rt;
    }

    if (nodoMovido->tam % BUFF) {
        fseek(arqBackup, posLeitura, SEEK_SET);
        rt = fread(buffer, sizeof(char), nodoMovido->tam % BUFF, arqBackup);
        fseek(arqBackup, posEscrita, SEEK_SET);
        fwrite(buffer, sizeof(char), nodoMovido->tam % BUFF, arqBackup);

        posLeitura += rt;
        posEscrita += rt;
    }    

    // remove o arquivo movido da posicao original
    int newTam = tamanhoArquivo(arqBackup);

    read = nodoMovido->b_fim + 1;
    newPos = nodoMovido->b_ini;

    while (read < newTam) {
        fseek(arqBackup, read, SEEK_SET);

        if (newTam - read > BUFF)
            rt = fread(buffer, 1, BUFF, arqBackup);
        else
            rt = fread(buffer, 1, newTam - read, arqBackup);

        fseek(arqBackup, newPos, SEEK_SET);
        fwrite(buffer, 1, rt, arqBackup);

        read += rt;
        newPos += rt;
    }

    ftruncate(fileno(arqBackup), tamArquivo);

    // ajusta os bits de inicio e fim no diretorio
    aux = f->ini;
    aux->b_ini = 4;
    aux->b_fim = aux->b_ini + aux->tam - 1;
    while (aux != f->fim) {
        aux->prox->b_ini = aux->b_fim + 1;   
        aux->prox->b_fim = aux->prox->b_ini + aux->prox->tam - 1;
        aux = aux->prox;
    }

    // reescreve o diretorio na ordem correta
    int posDiretorio;
    fseek(arqBackup, 0, SEEK_SET);
    fread(&posDiretorio, sizeof(int), 1, arqBackup);

    int tamFila = f->tamanho;
    fseek(arqBackup, posDiretorio, SEEK_SET);
    fwrite(&tamFila, sizeof(int), 1, arqBackup);
    
    lacoEscrita(f, arqBackup);
}
