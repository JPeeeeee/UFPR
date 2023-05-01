#define BUFF 255
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "libarquivochaves.h"


// funcao que gera o arquivo de chaves
void gera_arquivo_chaves(FILE *ArquivoChaves, fila_t *f) {
	nodo_f_t *aux = f->ini;

	// itera por toda a lista e printa a letra e chaves de cada nodo
    for (int i = 0; i < tamanho_fila(f); i++){
        fprintf(ArquivoChaves, "%c:", aux->letra);

        for (int j = 0; j < aux->tamanho; j++) {
            fprintf(ArquivoChaves, " %d", aux->chaves[j]);
        }

        fprintf(ArquivoChaves, "\n");
        aux = aux->prox;
    }
}

// cria a estrutura lista 
fila_t *cria_lista_encode(FILE *LivroCifra){
	fila_t *f = cria_fila();

	if (LivroCifra == NULL)
		return NULL;

	char palavra[BUFF];
	int p = 0;

	// le cada uma das letras do livro cifra e insere a primeira letra na estrutura fila
	while (fscanf(LivroCifra, "%s", palavra) != EOF) { 

		char primeira_letra;

		primeira_letra = palavra[0];

		// Para caso de um arquivo convertido para UTF-8, por exemplo, desconsidera os primeiros caracteres que avisam da conversão
		// if (p == 0){
		// 	primeira_letra = palavra[3];
		// }

		primeira_letra = tolower(primeira_letra);

		// so insere a letra na fila se ela existir nos 127 valores da tabela ASCII
		if (primeira_letra <= 127)
			insere_fila(f, primeira_letra, p);

		p++;
				
	}

	return f;
}