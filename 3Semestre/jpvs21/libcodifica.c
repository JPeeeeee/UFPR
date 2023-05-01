#define BUFF 255
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "libcodifica.h"
#include "libarquivochaves.h"


// algoritmo de codificacao da mensagem de entrada
void codifica_mensagem(fila_t *f, FILE *MensagemEntrada, FILE *MensagemSaida) {
	printf("Codificando Mensagem...\n");

	time_t t;
	srand((unsigned) time(&t));

	char letra;
	nodo_f_t *nodo_resultante;

	// le cada um dos char na mensagem de entrada e transforma em chaves
	while ((letra = fgetc(MensagemEntrada)) != EOF) {

		// se a letra estiver na tabela ascii normal transforma ela em minuscula e insere a chave na mensagem de saida
		if (letra <= 127){

			letra = tolower(letra);

			// nodo resultante recebe o nodo que contem o char letra se a letra existir no livro cifra
			nodo_resultante = busca_fila(f, letra);
			if (nodo_resultante != NULL){

				// escolhe uma chave aleatoria do vetor de chaves presente no nodo e insere ela na mensagem final
				fprintf(MensagemSaida, " %d", nodo_resultante->chaves[rand() % nodo_resultante->tamanho]);
			} else if (nodo_resultante == NULL && letra != ' ' && letra != '\n') {
				printf("ERRO! a letra '%c' utilizada na mensagem de entrada esta indisponivel no livro cifra!\n", letra);
				return;
			}
		}
		if (letra == ' ')
			fprintf(MensagemSaida, " -1");
		else if (letra == '\n')
			fprintf(MensagemSaida, " -2");
	}
	printf("Mensagem codificada!\n");
}

// funcao que gerencia as tarefas necessarias para criar a mensagem de saida
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