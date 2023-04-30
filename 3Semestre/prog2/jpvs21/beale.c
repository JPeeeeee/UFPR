#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <unistd.h>
#include "libfila.h"
#include "libcodifica.h"
#include "libdecodifica.h"

#define BUFF 255

void close_files(FILE *livro_cifra, FILE *mensagem_entrada, FILE *mensagem_saida, FILE *arquivo_chaves) {
    if (livro_cifra)
        fclose(livro_cifra);
    if (mensagem_entrada)
        fclose(mensagem_entrada);
    if (arquivo_chaves)
        fclose(arquivo_chaves);
    if (mensagem_saida)
        fclose(mensagem_saida);
}

int main(int argc, char *argv[]) {

    int option, flag_e = 0, flag_d = 0, flag_c = 0, flag_b = 0;
    FILE *livro_cifra = NULL;
    FILE *mensagem_entrada = NULL;
    FILE *arquivo_chaves = NULL;
    FILE *mensagem_saida = NULL;

    char *nomeArquivoChaves;

    while ((option = getopt (argc, argv, "edb:m:o:i:c:")) != -1)
        switch (option) {
            case 'e':      // opcao enconde

                flag_e = 1;
                
                break;

            case 'd':   

                flag_d = 1;   // opcao decode

                break;

            case 'o':      // nome do arquivo de mensagem de saida

                mensagem_saida = fopen(optarg, "w");

                break;

            case 'm':      // nome do arquivo de mensagem original

                mensagem_entrada = fopen(optarg, "r");

                break;

            case 'i':      // nome do arquivo de mensagem original

                mensagem_entrada = fopen(optarg, "r");

                break;

            case 'c':      // nome do arquivo de chaves

                // guarda o nome do arquivo de chaves na variavel nomeArquivoChaves
                // o arquivo nao eh aberto agora pois dependendo da opcao escolhida ele pode ser aberto em modo read ou write

                nomeArquivoChaves = optarg;
                flag_c = 1;

                break;

            case 'b':      // nome do livro cifra

                livro_cifra = fopen(optarg, "r");
                flag_b = 1;

                break;  

            default:
                break;
        }

    // opcao encode selecionada
    if (flag_e){

        // abre arquivo de chaves em modo write
        arquivo_chaves = fopen(nomeArquivoChaves, "w");

        if (livro_cifra == NULL || arquivo_chaves == NULL || mensagem_saida == NULL || mensagem_entrada == NULL){
            close_files(livro_cifra, mensagem_entrada, mensagem_saida, arquivo_chaves);
            return printf("Erro ao abrir um ou mais aquivos! Tente novamente!\n");
        }

        coleta_dados_texto_fila(livro_cifra, arquivo_chaves, mensagem_saida, mensagem_entrada);

    } else if (flag_d && flag_c && !flag_b) { // opcao decode com arquivo de chaves

        // abre arquivo de chaves em modo read
        arquivo_chaves = fopen(nomeArquivoChaves, "r");

        if (arquivo_chaves == NULL || mensagem_saida == NULL || mensagem_entrada == NULL){
            close_files(livro_cifra, mensagem_entrada, mensagem_saida, arquivo_chaves);
            return printf("Erro ao abrir um ou mais aquivos! Tente novamente!\n");
        }
        
        decodifica_mensagem_chaves(arquivo_chaves, mensagem_saida, mensagem_entrada);

    } else if (flag_d && flag_b && !flag_c) { // opcao decode com livro de chaves

        if (livro_cifra == NULL || mensagem_saida == NULL || mensagem_entrada == NULL){
            close_files(livro_cifra, mensagem_entrada, mensagem_saida, arquivo_chaves);
            return printf("Erro ao abrir um ou mais aquivos! Tente novamente!\n");
        }

        decodifica_mensagem_livro(livro_cifra, mensagem_saida, mensagem_entrada);

    } else { // erro nos argumentos na chamada do programa

        close_files(livro_cifra, mensagem_entrada, mensagem_saida, arquivo_chaves);

        printf("Erro ao abrir um ou mais aquivos! Tente novamente!\n");
        return -1;
    } 
        


    setlocale(LC_ALL,"");

    return 0;
}