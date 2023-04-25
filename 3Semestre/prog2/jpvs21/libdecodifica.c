#include <stdio.h>
#include "libdecodifica.h"

char encontra_letra(FILE *ArquivoChaves, int chave_letra_requerida) { 
    char letra, espaco;
    int numero;

    while (fscanf(ArquivoChaves, "%c:", &letra) != EOF) {

		espaco = fgetc(ArquivoChaves);
        fscanf(ArquivoChaves, "%d", &numero);

        while (espaco != '\n') {

            if (chave_letra_requerida == numero)
                return letra;

            fscanf(ArquivoChaves, "%d", &numero);
            espaco = fgetc(ArquivoChaves);
        }
	}

    return ' ';
}

void decodifica_mensagem_chaves(FILE *ArquivoChaves, FILE *MensagemSaida, FILE *MensagemEntrada) {

    int chave_letra_codificada;

    while (fscanf(MensagemEntrada, "%d", &chave_letra_codificada) != EOF) {
        if (chave_letra_codificada == -1)
            fprintf(MensagemSaida, " ");
        else
            fprintf(MensagemSaida, "%c", encontra_letra(ArquivoChaves, chave_letra_codificada));
    }

    return;
}