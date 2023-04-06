#define BUFF 255
#include <stdio.h>
#include <ctype.h>
#include "libcodifica.h"



void gera_arquivo_chaves(char *ArquivoChaves, fila_t *f) {
	nodo_f_t *aux = f->ini;

    for (int i = 0; i < tamanho_fila(f); i++){
        printf("%c: ", aux->letra);

        for (int j = 0; j < aux->tamanho; j++) {
            printf("%d ", aux->chaves[j]);
        }

        printf("\n");
        aux = aux->prox;
    }
}

void codifica_mensagem(fila_t *f, char *MensagemEntrada, char *MensagemSaida) {
	printf("Codificando Mensagem...\n");
	FILE *mensagem_saida, *mensagem_entrada;

    mensagem_saida = fopen(MensagemSaida, "w");
	mensagem_entrada = fopen(MensagemEntrada, "r");

	int p = 0;
	char *palavra = NULL;

	nodo_f_t *nodo_resultante;

	while (fscanf(mensagem_entrada, "%s", palavra) != EOF) {
		char primeira_letra;

		primeira_letra = palavra[0];

		if (p == 0)
			primeira_letra = palavra[1];

		primeira_letra = tolower(primeira_letra);

		nodo_resultante = busca_fila(f, primeira_letra);
		if (nodo_resultante != NULL)
			printf("letra do nodo resultante: %c\n", nodo_resultante->letra);
			

		p++;		
	}
}

void coleta_dados_texto_fila (char *LivroCifra, char *ArquivoChaves, char *MensagemSaida, char *MensagemEntrada) {
	FILE *livro_cifra, *arquivo_chaves, *mensagem_saida, *mensagem_entrada;

	fila_t *f = cria_fila();
	// // Lembrar de mudar para argc
	livro_cifra = fopen(LivroCifra, "r");
	arquivo_chaves = fopen(ArquivoChaves, "w");

	if (livro_cifra == NULL)
		return;


	printf("\n");


	char *palavra = NULL;

	int p = 0;

	while (fscanf(livro_cifra, "%s", palavra) != EOF) { //problema aqui
		printf(" entre aqui\n");
		char primeira_letra;

		// Rever com professor
		primeira_letra = palavra[0];

		if (p == 0)
		primeira_letra = palavra[1];

		primeira_letra = tolower(primeira_letra);

		if (primeira_letra >= 97 && primeira_letra <= 122)
			insere_fila(f, primeira_letra, p);

		p++;		
	}
	printf("Aqui que ta o BO\n");

	gera_arquivo_chaves(ArquivoChaves, f);
	codifica_mensagem(f, MensagemEntrada, MensagemSaida);

	fclose(livro_cifra);
	return;
}