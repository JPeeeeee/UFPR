#define BUFF 255
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "libcodifica.h"




void gera_arquivo_chaves(FILE *ArquivoChaves, fila_t *f) {
	nodo_f_t *aux = f->ini;

    for (int i = 0; i < tamanho_fila(f); i++){
        fprintf(ArquivoChaves, "%c: ", aux->letra);

        for (int j = 0; j < aux->tamanho; j++) {
            fprintf(ArquivoChaves, "%d ", aux->chaves[j]);
        }

        fprintf(ArquivoChaves, "\n");
        aux = aux->prox;
    }
}

fila_t *cria_lista_encode(FILE *LivroCifra){
	fila_t *f = cria_fila();

	if (LivroCifra == NULL)
		return NULL;

	char palavra[BUFF];

	int p = 0;
	while (fscanf(LivroCifra, "%s", palavra) != EOF) { 
		char primeira_letra;

		primeira_letra = palavra[0];

		if (p == 0){
			primeira_letra = palavra[3]; // ????????????
		}

		primeira_letra = tolower(primeira_letra);

		if (primeira_letra <= 127)
			insere_fila(f, primeira_letra, p);

		p++;		
	}

	return f;
}

void codifica_mensagem(fila_t *f, FILE *MensagemEntrada, FILE *MensagemSaida) {
	printf("Codificando Mensagem...\n");

	time_t t;
	srand((unsigned) time(&t));

	char letra;
	nodo_f_t *nodo_resultante;

	while ((letra = fgetc(MensagemEntrada)) != EOF) {
		if (letra <= 127){
			nodo_resultante = busca_fila(f, letra);

			if (nodo_resultante != NULL){
				fprintf(MensagemSaida, "%d ", nodo_resultante->chaves[rand() % nodo_resultante->tamanho]);
			} else if (nodo_resultante == NULL && letra != ' ') {
				printf("ERRO! Existem letras utilizadas na mensagem de entrada que estao indisponiveis no livro cifra!\n");
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