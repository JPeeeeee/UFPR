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

// Insere strings desejadas no vetor v e retorna o tamanho de v
int vetorizaStrings(FILE *arq, char** v){
    char ch;
    char *str = malloc(sizeof(char) * 512); // string auxiliar
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
            
            v[i] = malloc(sizeof(char) * 512); // Aloca espaco para a string dentro do vetor
            strcpy(v[i], str); // copia a string para dentro do vetor
            printf("string: %s\n", v[i]);
            i++; // itera "i", o numero de elementos no vetor
            strcpy(str, ""); // limpa a string str
        }
    };
    free(str);
    return i;
}

// fazer funcao especifica para comparar strings usando encontrar tag
char *descobreNivelPeriodicos(char ch, FILE *arq, char *string){
    if (encontrarTag(ch, arq, string)){
        printf("ACHEEEEEEEEEEEEEI\n");
        return "oioioi";
    }
    printf("num achei :(\n")
    return "oiioio";
}

int main()
{
    FILE* arq;
    char **vetor_s = malloc(sizeof(char) * 512 * 512);
    char **A1 = malloc(sizeof(char) * 512 * 512);
    char **A2 = malloc(sizeof(char) * 512 * 512);
    char **A3 = malloc(sizeof(char) * 512 * 512);
    char **A4 = malloc(sizeof(char) * 512 * 512);
    char **B1 = malloc(sizeof(char) * 512 * 512);
    char **B2 = malloc(sizeof(char) * 512 * 512);
    char **B3 = malloc(sizeof(char) * 512 * 512);
    char **B4 = malloc(sizeof(char) * 512 * 512);
    char **C = malloc(sizeof(char) * 512 * 512);

    //encontrar jeito de transformar a filtragem dos periodicos

    
    // Abre o arquivo em modo de leitura
    arq = fopen("curriculo.xml", "r");
 
    if (NULL == arq) {
        // Caso nao consiga abrir o arquivo termina o programa
        printf("file can't be opened \n");
        return 0;
    }
    char ch = fgetc(arq);
    // Acessa coloca todos os periodicos ou revistas em uma variavel
    int tam = vetorizaStrings(arq, vetor_s);

    for (int j = 0; j < tam; j++)
        free(vetor_s[j]);

    free(vetor_s);
 // Libera string auxiliar
    // Fecha arquivo
    fclose(arq);
    return 0;
}