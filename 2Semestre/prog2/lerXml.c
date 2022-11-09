#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define qualisConf "qualis-conf.txt"
#define qualisPeriodicos "qualis-periodicos.txt"
 
int encontrarTag (char ch, FILE* arq, char *chave){
    // Salva o tamanho da chave
    int chaveLen = strlen(chave);
    int i;
    // Enquanto i for menor do que o tamanho da chave
    for (i = 0; i < chaveLen; i++){
        // Confere se o caractere ch esta de acordo com a chave
        if (ch != chave[i])
            return 0;

        // Pega o proximo caractere e itera i
        ch = fgetc(arq);
    }
    // A chave foi encontrada
    return 1;
}

void sumarizarPeriodicosOuRevistas(FILE *arq){
    char ch;
    char *str = malloc(sizeof(char) * 512);
    char **periodicoOuRevista = malloc(512 * 512);
    int i = 0;
    // Enquanto o arquivo nao acabar
     while (ch != EOF) {
        ch = fgetc(arq);
        
        // Encontra a a propriedade periodico ou revista no arquivo XML
        if (encontrarTag(ch, arq, "STA=")){
            ch = fgetc(arq);
            while (ch != '\"'){
                strncat(str, &ch, 1);
                ch = fgetc(arq);
            }
            
            //arrumar problema malloc
            periodicoOuRevista[i] = malloc(sizeof(str) + 1);
            strcpy(periodicoOuRevista[i], str);
            printf("string: %s\n", periodicoOuRevista[i]);
            i++;
            strcpy(str, "");
        }
    };
}

// fazer funcao especifica para comparar strings usando encontrar tag

int main()
{
    FILE* arq;


    // Abre o arquivo em modo de leitura
    arq = fopen("curriculo.xml", "r");
 
    if (NULL == arq) {
        // Caso nao consiga abrir o arquivo termina o programa
        printf("file can't be opened \n");
        return 0;
    }

    // Acessa coloca todos os periodicos ou revistas em uma variavel
    sumarizarPeriodicosOuRevistas(arq);
 
    // Fecha arquivo
    fclose(arq);
    return 0;
}