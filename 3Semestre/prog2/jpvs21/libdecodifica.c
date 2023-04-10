#include <stdio.h>
#include "libdecodifica.h"

fila_t *cria_lista_decode(FILE *ArquivoChaves) { // Descobrir como ler int diferente de char e ler linha ate \n dinamicamente ler linha por linha
    fila_t *f = cria_fila();
    char letra;
    char *chave = NULL;

    while ((letra = fgetc(ArquivoChaves)) != EOF) {
		if (letra == '\n'){
            chave++;
		} else if (letra == ':') {
            fscanf(ArquivoChaves, "%[^\n]s", chave);
                printf("chaves = %s\n", chave); // rever aqui
        }
	}

    return f;
}

char busca_letra(FILE *ArquivoChaves, fila_t *f) {
    char letra = '\0';
    return letra;
}

void decodifica_mensagem_chaves(FILE *ArquivoChaves, FILE *MensagemSaida, FILE *MensagemEntrada) {
    cria_lista_decode(ArquivoChaves);
    return;
}