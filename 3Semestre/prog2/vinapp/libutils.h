
#include <stdio.h>
#include <stdlib.h>

// imprime a estrutura diretorio do arquivo backup
void imprimeDiretorio(fila_t *f);

// escreve as informacoes presentes em cada nodo do diretorio para dentro do arquivo backup
void lacoEscrita(fila_t *f, FILE *arqBackup);

// organiza os bits de inicio do diretorio, tamanho da estrutura e escreve o diretorio no arquivo backup
void escreveDiretorio(fila_t *f, FILE *arqBackup);

// le o diretorio presente no arquivo backup e carrega as informacoes para uma estrutura de dados em memoria
void leDiretorio(fila_t *f, FILE *arqBackup);

// retorna um inteiro que representa o tamanho de um arquivo
int tamanhoArquivo(FILE *arq);

// remove os bytes entre 'comeco' e 'fim' e escreve o que estava logo abaixo deles para cima
int removeBytes(FILE *arqBackup, int comeco, int fim);
