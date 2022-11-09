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

char** vetorizaStrings(FILE *arq){
    char ch;
    char *str = malloc(sizeof(char) * 512); // string auxiliar
    char** periodicoOuRevista = malloc(sizeof(str) * 512); // Vetor de strings
    int i = 0;

    // Enquanto o arquivo nao acabar
    while (ch != EOF) {
        ch = fgetc(arq); // Chama o proximo char

        // Encontra a a propriedade periodico ou revista no arquivo XML
        if (encontrarTag(ch, arq, "STA=")){
            ch = fgetc(arq); // Pula a primeira aspa após o sinal de igualdade

            while (ch != '\"'){
                strncat(str, &ch, 1); // Concatena o char na string str
                ch = fgetc(arq); // Pega o proximo char
            }
            
            periodicoOuRevista[i] = malloc(sizeof(char) * 512); // Aloca espaco para a string dentro do vetor
            strcpy(periodicoOuRevista[i], str); // copia a string para dentro do vetor
            printf("string: %s\n", periodicoOuRevista[i]);
            i++; // itera "i", o numero de elementos no vetor
            strcpy(str, ""); // limpa a string str
        }
    };

    for (int j = 0; j < i; j++)
        free(periodicoOuRevista)

    free(str);

}

// fazer funcao especifica para comparar strings usando encontrar tag

int main()
{
    FILE* arq;
    char **periodicosOuRevistas;

    // Abre o arquivo em modo de leitura
    arq = fopen("curriculo.xml", "r");
 
    if (NULL == arq) {
        // Caso nao consiga abrir o arquivo termina o programa
        printf("file can't be opened \n");
        return 0;
    }

    // Acessa coloca todos os periodicos ou revistas em uma variavel
    periodicosOuRevistas = vetorizaStrings(arq);
    // Fecha arquivo
    fclose(arq);
    return 0;
}