#define BUFF 255
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "libcodifica.h"
#include "libarquivochaves.h"

void codifica_mensagem(fila_t *f, FILE *MensagemEntrada, FILE *MensagemSaida) {
	printf("Codificando Mensagem...\n");

	time_t t;
	srand((unsigned) time(&t));

	char letra;
	nodo_f_t *nodo_resultante;

	while ((letra = fgetc(MensagemEntrada)) != EOF) {

		if (letra <= 127){
			letra = tolower(letra);
			nodo_resultante = busca_fila(f, letra);

			if (nodo_resultante != NULL){
				fprintf(MensagemSaida, "%d ", nodo_resultante->chaves[rand() % nodo_resultante->tamanho]);
			} else if (nodo_resultante == NULL && letra != ' ') {
				printf("ERRO! a letra '%c' utilizada na mensagem de entrada esta indisponivel no livro cifra!\n", letra);
				return;
			}
		}
		if (letra == ' ')
			fprintf(MensagemSaida, "-1 ");
	}
	printf("Mensagem codificada!\n");
}

void coleta_dados_texto_fila (FILE *LivroCifra, FILE *ArquivoChaves, FILE *MensagemSaida, FILE *MensagemEntrada) {

	fila_t *f = cria_lista_encode(LivroCifra);

	gera_arquivo_chaves(ArquivoChaves, f);
	codifica_mensagem(f, MensagemEntrada, MensagemSaida);


	destroi_fila(f);
	fclose(LivroCifra);
	fclose(ArquivoChaves);
	fclose(MensagemEntrada);
	fclose(MensagemSaida);

	return;
}