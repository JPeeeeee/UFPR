#include <stdio.h>
#include "libfila.h"
#include "libutils.h"

// escreve o arquivo no backup utilizando a leitura e escrita bufferizada
void transcreveArquivo (FILE *arqBackup, char *arquivo, fila_t *diretorio);

// inclui o arquivo no backup e organiza o diretorio
void inclusaoDeArquivo (FILE *arqBackup, char *nome, int optA, fila_t *diretorio);

// remove o arquivo do backup e organiza o diretorio
void removeArquivo(char *nome, FILE *arqBackup, fila_t *f);

// extrai os arquivos desejados do backup
void extraiArquivo(char *nome, FILE *arqBackup, fila_t *f);

// move o arquivo desejado para a posicao logo abaixo do arquivo especificado na chamada do programa
void moveArquivo(char *movido, char *anterior, FILE *arqBackup, fila_t *f);