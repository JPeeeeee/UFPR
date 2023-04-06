#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <wchar.h>
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

    fila_t *f = cria_fila();
    char *LivroCifra, *ArquivoChaves, *MensagemSaida, *MensagemEntrada, *MensagemOriginal;
    int option, flag_e, flag_d;

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
                MensagemSaida = optarg;
                printf("usou o: %s\n", optarg);
                break;

            case 'm':      // option -m was set
                MensagemOriginal = optarg;
                printf("usou o: %s\n", optarg);
                break;

            case 'i':      // option -i was set
                MensagemEntrada = optarg;
                printf("usou i: %s\n", optarg);
                break;

            case 'c':      // option -c was set
                ArquivoChaves = optarg;
                printf("usou c: %s\n", optarg);
                break;

            case 'b':      // option -b was set
                LivroCifra = optarg;    
                printf("usou b: %s\n", optarg);
                break;  

            default:
                break;
        }

    if (flag_e)
        coleta_dados_texto_fila()
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

    nodo_f_t *aux = f->ini;

    for (int i = 0; i < tamanho_fila(f); i++){
        printf("%lc: ", aux->letra);

    for (int j = 0; j < aux->tamanho; j++) {
        printf("%d ", aux->chaves[j]);
    }

        printf("\n");
        aux = aux->prox;
    }

    return 0;
}