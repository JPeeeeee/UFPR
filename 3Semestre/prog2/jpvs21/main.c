#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <unistd.h>
#include "libfila.h"
#include "libcodifica.h"
#include "libarvore.h"

#define BUFF 255

// nodo_t *coleta_dados_texto_RB(FILE *livro_cifra){
//     wchar_t palavra[BUFF];
//     nodo_t *raiz = NULL;

//     int p = 0;

//     fscanf(livro_cifra, "%ls", palavra);
//     while (fscanf(livro_cifra, "%ls", palavra) != EOF) {

//         wchar_t primeira_letra = palavra[0];

//         if (raiz == NULL){
//             raiz = inclui_rb(NULL, primeira_letra, p);
//         }
//         else{
//             inclui_rb(raiz, primeira_letra, p);
//         }

//         p++;		
//     }
//     printf("cabou a coleta\n");
//     return raiz;
// }


int main(int argc, char *argv[]) {

    int option, flag_e, flag_d;
    FILE *livro_cifra = NULL;
    FILE *mensagem_entrada = NULL;
    FILE *arquivo_chaves = NULL;
    FILE *mensagem_saida = NULL;

    while ((option = getopt (argc, argv, "edb:m:o:i:c:")) != -1)
        switch (option) {
            case 'e':      // option -e was set
                flag_e = 1;
                printf("usou e\n");
                break;

            case 'd':   
                flag_d = 1;   // option -d was set
                printf("usou d: %s\n", optarg);
                break;

            case 'o':      // option -o was set
                mensagem_saida = fopen(optarg, "w");
                printf("usou o: %s\n", optarg);
                break;

            case 'm':      // option -m was set
                mensagem_entrada = fopen(optarg, "r");
                printf("usou o: %s\n", optarg);
                break;

            case 'i':      // option -i was set
                mensagem_entrada = fopen(optarg, "r");
                printf("usou i: %s\n", optarg);
                break;

            case 'c':      // option -c was set
                arquivo_chaves = fopen(optarg, "w");
                printf("usou c: %s\n", optarg);
                break;

            case 'b':      // option -b was set
                livro_cifra = fopen(optarg, "r");
                printf("usou b: %s\n", optarg);
                break;  

            default:
                break;
        }

    if (flag_e){
        if (livro_cifra == NULL)
            return -1;
        coleta_dados_texto_fila(livro_cifra, arquivo_chaves, mensagem_saida, mensagem_entrada);
    }
    else if (flag_d)

    // while (argv[argv_counter]){
    //     if (argv[argv_counter][0] == '-') {
    //         char letra = argv[argv_counter][1];
    //         switch (letra) {

    //             // Letra b
    //             case 98: {
    //                 printf("letra b\n");
    //             }
    //             break;

    //             // Letra c
    //             case 99: {
    //                 printf("letra c\n");
    //             }
    //             break;

    //             // Letra d
    //             case 100: {
    //                 printf("letra d\n");
    //             }
    //             break;

    //             // Letra e
    //             case 101: {
    //                 // if (argv[argv_counter][1] == 'e') // Perguntar se precisa lidar com acentos e letras maiusculas e se a ordem de execucao do programa tem que ser sempre com os parametros na mesma ordem 

    //                 //     break;
    //                 f = coleta_dados_texto_fila(argv[argv_counter + 1]);
    //             }
    //             break;

    //             // Letra i
    //             case 105: {
    //                 printf("letra i\n");
    //             }
    //             break;

    //             // Letra m
    //             case 109: {
    //                 printf("letra m\n");
    //             }
    //             break;

    //             // Letra o
    //             case 111: {
    //                 printf("letra o\n");
    //             }
    //             break;

    //             default:
    //                 break;
    //         }
    //     }
    //     argv_counter++;
    // }


    setlocale(LC_ALL,"");

    return 0;
}