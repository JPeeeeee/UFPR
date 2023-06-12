#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>
#include "libmanagefiles.h"

void transcreveArquivo (FILE *arqBackup, char *arquivo) {

    char c;
    
    struct stat info;

    FILE *arqTranscrever = fopen(arquivo, "r");

    if (!arqTranscrever)
        return;

    stat(arquivo, &info);

    printf("tamanho do arquivo: %lld\n", info.st_size);

    for (int i = 0; i < info.st_size; i++){
        fread(&c, sizeof(char), 1, arqTranscrever);
        fwrite(&c, sizeof(char), 1, arqBackup);
    }

    printf("\n");

    fclose(arqTranscrever);
}

void inclusaoDeArquivo (int argc, char **argumentos) {

    struct stat info;

    FILE *arqBackup = fopen(argumentos[2], "a+");

    if (!arqBackup)
        return;

    for (int argAtual = 3; argAtual < argc; argAtual++) {
        stat(argumentos[argAtual], &info);

        printf("nome do arquivo: %s\n", argumentos[argAtual]);

        // printf("tempo da ultima alteracao: %ld\n", (time(0) - info.st_mtimespec.tv_sec) / 60);

        transcreveArquivo(arqBackup, argumentos[argAtual]);
    }
}