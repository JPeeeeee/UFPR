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

int tamanhoArquivo(FILE *arq) {
    struct stat info;

    fstat(fileno(arq), &info);
    return info.st_size;
}

void output_permissions(mode_t m) {
    putchar( m & S_IRUSR ? 'r' : '-' );
    putchar( m & S_IWUSR ? 'w' : '-' );
    putchar( m & S_IXUSR ? 'x' : '-' );
    putchar( m & S_IRGRP ? 'r' : '-' );
    putchar( m & S_IWGRP ? 'w' : '-' );
    putchar( m & S_IXGRP ? 'x' : '-' );
    putchar( m & S_IROTH ? 'r' : '-' );
    putchar( m & S_IWOTH ? 'w' : '-' );
    putchar( m & S_IXOTH ? 'x' : '-' );
}

// funcao que imprime as informacoes de cada nodo presente na estrutura diretorio
void imprimeDiretorio(fila_t *f) {
    nodo_f_t *novo = f->ini;
    if (!novo){
        printf("diretorio vazio\n");
        return;
    }
    printf("\n");
    while (novo != NULL) {    
        char *time = ctime(&novo->dataAlteracao);
        time[strlen(time) - 1] = '\0';
        struct passwd *pw = getpwuid(novo->UID);
        struct group *gr = getgrgid(novo->group);
        output_permissions(novo->permissoes);
        printf("%s %s %8lld %s %s\n", pw->pw_name, gr->gr_name, novo->tam, time, novo->nome);
        novo = novo->prox;
    }
    printf("\n");
}

// funcao que imprime no arquivo os dados de cada nodo na estrutura diretorio
void lacoEscrita(fila_t *f, FILE *arqBackup) {
    nodo_f_t *novo = f->ini;
    while (novo) {
        int tamNome = strlen(novo->nome);
        fwrite(&tamNome, sizeof(int), 1, arqBackup);
        fwrite(novo->nome, sizeof(char), strlen(novo->nome), arqBackup);
        int tamPath = strlen(novo->path);
        fwrite(&tamPath, sizeof(int), 1, arqBackup);
        fwrite(novo->path, sizeof(char), strlen(novo->path), arqBackup);
        fwrite(&novo->UID, sizeof(uid_t), 1, arqBackup);
        fwrite(&novo->group, sizeof(gid_t), 1, arqBackup);
        fwrite(&novo->dataAlteracao, sizeof(time_t), 1, arqBackup);
        fwrite(&novo->posicao, sizeof(int), 1, arqBackup);
        fwrite(&novo->tam, sizeof(off_t), 1, arqBackup);
        fwrite(&novo->b_ini, sizeof(int), 1, arqBackup);
        fwrite(&novo->b_fim, sizeof(int), 1, arqBackup);
        fwrite(&novo->permissoes, sizeof(mode_t), 1, arqBackup);
        novo = novo->prox;
    }
}

// funcao que escreve as informacoes necessarias no arquivo backup
void escreveDiretorio(fila_t *f, FILE *arqBackup){

    int comecoDiretorio, tamFila;
    comecoDiretorio = f->fim->b_fim + 1;
    tamFila = tamanho_fila(f);

    fseek(arqBackup, 0, SEEK_SET);
    fwrite(&comecoDiretorio, sizeof(int), 1, arqBackup);
    fseek(arqBackup, comecoDiretorio, SEEK_SET);
    fwrite(&tamFila, sizeof(int), 1, arqBackup);
    
    lacoEscrita(f, arqBackup);
}


void leDiretorio(fila_t *f, FILE *arqBackup) {
    
    int comecoDiretorio, tamFila, tamNome, tamPath;

    // encontra o bit de inicio do diretorio e le o tamanho dele
    fread(&comecoDiretorio, sizeof(int), 1, arqBackup);
    fseek(arqBackup, comecoDiretorio, SEEK_SET);
    fread(&tamFila, sizeof(int), 1, arqBackup);

    // monta a estrutura de dados diretorio
    for (int i = 0; i < tamFila; i++) {
        nodo_f_t *novo = malloc(sizeof(nodo_f_t));
        novo->prox = NULL;
        fread(&tamNome, sizeof(int), 1, arqBackup);
        novo->nome = malloc(sizeof(char) * (tamNome));
        fread(novo->nome, sizeof(char), tamNome, arqBackup);
        fread(&tamPath, sizeof(int), 1, arqBackup);
        novo->path = malloc(sizeof(char) * (tamPath));
        fread(novo->path, sizeof(char), tamPath, arqBackup);
        fread(&novo->UID, sizeof(uid_t), 1, arqBackup);
        fread(&novo->group, sizeof(gid_t), 1, arqBackup);
        fread(&novo->dataAlteracao, sizeof(time_t), 1, arqBackup);
        fread(&novo->posicao, sizeof(int), 1, arqBackup);
        fread(&novo->tam, sizeof(off_t), 1, arqBackup);
        fread(&novo->b_ini, sizeof(int), 1, arqBackup);
        fread(&novo->b_fim, sizeof(int), 1, arqBackup);
        fread(&novo->permissoes, sizeof(mode_t), 1, arqBackup);
        insere_nodo_fila(f, novo);
    }
}

int removeBytes(FILE *arqBackup, int comeco, int fim) {
    char buffer[BUFF];
    int size = tamanhoArquivo(arqBackup);
    int read = fim + 1;
    int write = comeco;
    int rt, iniDiretorio;

    // encontra o inicio do direorio
    fseek(arqBackup, 0, SEEK_SET);
    fread(&iniDiretorio, sizeof(int), 1, arqBackup);

    if (comeco > fim) 
        return 1;
	if (fim > size) 
        return 2;

    // caso queria excluir os ultimos bits do arquivo
    // trunca o arquivo para antes do que precisa ser excluido
	if (read == size){
		ftruncate(fileno(arqBackup), comeco);
		return 0;
	}

    // escreve para cima tudo que estava para baixo do que precisa ser excluido
    while (read < size) {
        fseek(arqBackup, read, SEEK_SET);

        if (size - read > BUFF)
            rt = fread(buffer, 1, BUFF, arqBackup);
        else
            rt = fread(buffer, 1, size - read, arqBackup);

        fseek(arqBackup, write, SEEK_SET);
        fwrite(buffer, 1, rt, arqBackup);

        read += rt;
        write += rt;
    }

    rewind(arqBackup);
    ftruncate(fileno(arqBackup), size - ((fim - comeco + 1) + (size - iniDiretorio)));
    
    return 1;
}
