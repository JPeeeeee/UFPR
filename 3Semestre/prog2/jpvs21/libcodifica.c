#define BUFF 255
#include <stdio.h>
#include <ctype.h>
#include <string.h>
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

fila_t *cria_lista(FILE *LivroCifra){
	fila_t *f = cria_fila();

	if (LivroCifra == NULL)
		return NULL;

	char palavra[BUFF];

	int p = 0;
	while (fscanf(LivroCifra, "%s", palavra) != EOF) { 
		char primeira_letra;

		primeira_letra = palavra[0];

		if (p == 0){
			printf("palavra eh: %s\n", palavra);
			primeira_letra = palavra[3];
			printf("a primeira letra eh: %c\n", primeira_letra);
		}

		primeira_letra = tolower(primeira_letra);

		if (primeira_letra >= 97 && primeira_letra <= 122)
			insere_fila(f, primeira_letra, p);

		p++;		
	}

	return f;
}

void codifica_mensagem(fila_t *f, FILE *MensagemEntrada, FILE *MensagemSaida) {
	printf("Codificando Mensagem...\n");

	int p = 0;
	char palavra[BUFF];

	nodo_f_t *nodo_resultante;
	while (fscanf(MensagemEntrada, "%s", palavra) != EOF) {
		char primeira_letra;
		printf("palavra eh: %s\n", palavra);
		primeira_letra = palavra[0];

		primeira_letra = tolower(primeira_letra);
		printf("a primeira letra eh: %c\n", primeira_letra);

		nodo_resultante = busca_fila(f, primeira_letra);

		if (nodo_resultante != NULL)
			printf("letra do nodo resultante: %c\n", nodo_resultante->letra);
			

		p++;		
	}
}

void coleta_dados_texto_fila (FILE *LivroCifra, FILE *ArquivoChaves, FILE *MensagemSaida, FILE *MensagemEntrada) {
	if ((ArquivoChaves == NULL) || (LivroCifra == NULL) || (MensagemEntrada == NULL) || (MensagemSaida == NULL))
		return;

	fila_t *f = cria_lista(LivroCifra);

	printf("\n");

	gera_arquivo_chaves(ArquivoChaves, f);
	codifica_mensagem(f, MensagemEntrada, MensagemSaida);

	fclose(LivroCifra);
	fclose(ArquivoChaves);
	fclose(MensagemEntrada);
	fclose(MensagemSaida);

	return;
}