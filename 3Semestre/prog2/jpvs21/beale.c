#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <unistd.h>
#include "libfila.h"
#include "libcodifica.h"
#include "libdecodifica.h"

#define BUFF 255

int main(int argc, char *argv[]) {

    int option, flag_e = 0, flag_d = 0, flag_c = 0, flag_b = 0;
    FILE *livro_cifra = NULL;
    FILE *mensagem_entrada = NULL;
    FILE *arquivo_chaves = NULL;
    FILE *mensagem_saida = NULL;

    while ((option = getopt (argc, argv, "edb:m:o:i:c:")) != -1)
        switch (option) {
            case 'e':      // option -e was set
                flag_e = 1;
                break;

            case 'd':   
                flag_d = 1;   // option -d was set
                break;

            case 'o':      // option -o was set
                mensagem_saida = fopen(optarg, "w");
                break;

            case 'm':      // option -m was set
                mensagem_entrada = fopen(optarg, "r");
                break;

            case 'i':      // option -i was set
                mensagem_entrada = fopen(optarg, "r");
                break;

            case 'c':      // option -c was set
                arquivo_chaves = fopen(optarg, "w");
                flag_c = 1;
                break;

            case 'b':      // option -b was set
                livro_cifra = fopen(optarg, "r");
                flag_b = 1;
                break;  

            default:
                break;
        }

    if (flag_e){
        if (livro_cifra == NULL || arquivo_chaves == NULL || mensagem_saida == NULL || mensagem_entrada == NULL)
            return printf("Erro ao abrir um ou mais aquivos! Tente novamente!\n");

        coleta_dados_texto_fila(livro_cifra, arquivo_chaves, mensagem_saida, mensagem_entrada);
    } else if (flag_d && flag_c) {
        if (arquivo_chaves == NULL || mensagem_saida == NULL || mensagem_entrada == NULL)
            return printf("Erro ao abrir um ou mais aquivos! Tente novamente!\n");
        
        decodifica_mensagem_chaves(arquivo_chaves, mensagem_entrada, mensagem_saida);
    } else if (flag_d && flag_b) {
        if (livro_cifra == NULL || mensagem_saida == NULL || mensagem_entrada == NULL)
            return printf("Erro ao abrir um ou mais aquivos! Tente novamente!\n");
    }

    setlocale(LC_ALL,"");

    return 0;
}