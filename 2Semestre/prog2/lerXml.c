#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define qualisConf "qualis-conf.txt"
#define qualisPeriodicos "qualis-periodicos.txt"
 
int encontrarTag (char *ch, FILE* arq, char *chave){
    // Salva o tamanho da chave
    int chaveLen = strlen(chave);
    int i;
    // Enquanto i for menor do que o tamanho da chave
    for (i = 0; i < chaveLen; i++){
        // Confere se o caractere ch esta de acordo com a chave
        if (*ch != chave[i])
            return 0;

        // Pega o proximo caractere e itera i
        *ch = fgetc(arq);
    }
    // A chave foi encontrada
    return 1;
}
// fazer funcao especifica para comparar strings usando encontrar tag

int main()
{
    FILE* arq;
    char ch;
    char *stringDado = malloc(sizeof(char) * 512);

    // Abre o arquivo em modo de leitura
    arq = fopen("curriculo.xml", "r");
 
    if (NULL == arq) {
        // Caso nao consiga abrir o arquivo termina o programa
        printf("file can't be opened \n");
        return 0;
    }
 
    // Enquanto o arquivo nao acabar
     while (ch != EOF) {
        ch = fgetc(arq);
        if (encontrarTag(&ch, arq, "STA=\"")){
            while (ch != '\"'){
                strncat(stringDado, &ch, 1);
                ch = fgetc(arq);
            }
            printf("string: %s\n", stringDado);
            strcpy(stringDado, "");
        }
    };
 
    // Fecha arquivo
    fclose(arq);
    return 0;
}