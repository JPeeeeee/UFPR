#include <stdio.h>
#include "libdecodifica.h"

fila_t *cria_lista(FILE *ArquivoChaves) { // Descobrir como ler int diferente de char e ler linha ate \n dinamicamente
    fila_t *f = cria_fila();
    char letra, letra_anterior = NULL;

    while ((letra = fgetc(ArquivoChaves)) != EOF) {
		if (letra <= 127){
            if (letra_anterior == '\n' || letra_anterior == NULL){
                
            }

		}
	}
}

char busca_letra(FILE *ArquivoChaves, fila_t *f) {
    char letra, letra_anterior = NULL;

    return letra;
}

void decodifica_mensagem_chaves(FILE *ArquivoChaves, FILE *MensagemSaida, FILE *MensagemEntrada) {

    return;
}