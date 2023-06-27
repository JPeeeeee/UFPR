#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <grp.h>
#include <pwd.h>
#include "libmanagefiles.h"
#include "libfila.h"
#include "libutils.h"



int main(int argc, char *argv[]) {

    int RESERVED_SPACE = -1;

    fila_t *diretorio = cria_fila();

    int option, argCount;

    FILE *arqBackup;

    arqBackup = fopen(argv[2], "rb+");

    while ((option = getopt (argc, argv, "iamxrch")) != -1) {
        switch (option) {
            case 'i':
                if (argc < 4){
                    printf("Poucos argumentos na chamada do programa!\n");
                    return -1;
                }

                if (!arqBackup){
                    arqBackup = fopen(argv[2], "w+");
                    fwrite(&RESERVED_SPACE, sizeof(int), 1, arqBackup);
                } else {
                    leDiretorio(diretorio, arqBackup);
                }


                for (argCount = 3; argCount < argc; argCount++) {
                    char newName[strlen(argv[argCount]) + 2];
                    strcpy(newName, "./");
                    strncat(newName, argv[argCount], strlen(argv[argCount])); 
                    strncat(newName, "\0", strlen(argv[argCount]) + 1); 
                    inclusaoDeArquivo(arqBackup, argv[argCount], 0, diretorio);
                }
                if (fila_vazia(diretorio))
                    return -1;
                free(diretorio);
                rewind(arqBackup);
                fclose(arqBackup);
                break;

            case 'a':
                if (argc < 4){
                    printf("Poucos argumentos na chamada do programa!\n");
                    return -1;
                }

                if (!arqBackup){
                    arqBackup = fopen(argv[2], "w+");
                    fwrite(&RESERVED_SPACE, sizeof(int), 1, arqBackup);
                } else {
                    leDiretorio(diretorio, arqBackup);
                }

                for (argCount = 3; argCount < argc; argCount++) {
                    char newName[strlen(argv[argCount]) + 2];
                    strcpy(newName, "./");
                    strncat(newName, argv[argCount], strlen(argv[argCount])); 
                    inclusaoDeArquivo(arqBackup, newName, 0, diretorio);
                }

                if (fila_vazia(diretorio)){
                    printf("diretorio vazio\n");
                    return -1;
                }
                fclose(arqBackup);
                break;

            case 'm':
                if (arqBackup)
                    leDiretorio(diretorio, arqBackup);
                
                moveArquivo(argv[3], argv[4], arqBackup, diretorio);
                imprimeDiretorio(diretorio);
                break;

            case 'x':
                if (argc < 4){
                    printf("Poucos argumentos na chamada do programa!\n");
                    return -1;
                }

                if (!arqBackup){
                    arqBackup = fopen(argv[2], "w+");
                    fwrite(&RESERVED_SPACE, sizeof(int), 1, arqBackup);
                } else {
                    leDiretorio(diretorio, arqBackup);
                }
                for (argCount = 3; argCount < argc; argCount++)
                    extraiArquivo(argv[argCount], arqBackup, diretorio);
                if (fila_vazia(diretorio))
                    return -1;
                free(diretorio);
                fclose(arqBackup);
                break;

            case 'r':
                if (argc < 4){
                    printf("Poucos argumentos na chamada do programa!\n");
                    return -1;
                }

                if (arqBackup)
                    leDiretorio(diretorio, arqBackup);

                for (argCount = 3; argCount < argc; argCount++)
                    removeArquivo(argv[argCount], arqBackup, diretorio);

                if (tamanhoArquivo(arqBackup) <= sizeof(int) || diretorio->tamanho == 0){
                    printf("Nao existem mais arquivos! Arquivo backup excluido ou inexistente!\n");
                    remove(argv[2]);
                    return 1;
                }
                free(diretorio);
                fclose(arqBackup);
                break;

            case 'c':                
                if (arqBackup)
                    leDiretorio(diretorio, arqBackup);
                imprimeDiretorio(diretorio);
                break;

            case 'h':
                printf("===================================\n");
                printf("\n            Modo de uso:\n");
                printf("\n./vina++ <opcao> <archive> [membro1 membro2 ...]\n");
                printf("\n===================================\n");
                printf("\n               Opcoes:\n");
                printf("\n-i : insere/acrescenta um ou mais membros ao archive. Caso o membro já exista no archive, ele deve ser substituído. Novos membros são inseridos respeitando a ordem da linha de comando, ao final do archive\n");
                printf("\n-a : mesmo comportamento da opção -i, mas a substituição de um membro existente ocorre APENAS caso o parâmetro seja mais recente que o arquivado\n");
                printf("\n-m target : move o membro indicado na linha de comando para imediatamente depois do membro target existente em archive. A movimentação deve ocorrer na seção de dados do archive\n");
                printf("\n-x : extrai os membros indicados de archive. Se os membros não forem indicados, todos devem ser extraídos. A extração consiste em ler o membro de archive e criar um arquivo correspondente, com conteúdo idêntico, em disco\n");
                printf("\n-r : remove os membros indicados de archive\n");
                printf("\n-c : lista o conteúdo de archive em ordem, incluindo as propriedades de cada membro (nome, UID, permissões, tamanho e data de modificação) e sua ordem no arquivo. A saída esperada é igual ao do comando tar com as opções tvf\n");
                printf("\n-h : imprime uma pequena mensagem de ajuda com as opções disponíveis e encerra\n");
                printf("\n===================================\n");
                break;
            
            default:
                break;
        }
    }

    return 0;
}