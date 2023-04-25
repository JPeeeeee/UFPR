#include <stdio.h>
#include "libdecodifica.h"
#include "libarquivochaves.h"

char encontra_letra_arquivo_chaves(FILE *ArquivoChaves, int chave_letra_requerida) { 
    rewind(ArquivoChaves);
    char letra, espaco;
    int numero;

    while (fscanf(ArquivoChaves, "%c:", &letra) != EOF) {

		espaco = fgetc(ArquivoChaves);
        fscanf(ArquivoChaves, "%d", &numero);

        while (espaco != '\n') {
            espaco = fgetc(ArquivoChaves);
            if (chave_letra_requerida == numero){
                return letra;
            }
            fscanf(ArquivoChaves, "%d", &numero);
        }
	}
    return ' ';
}

void decodifica_mensagem_chaves(FILE *ArquivoChaves, FILE *MensagemSaida, FILE *MensagemEntrada) {
	printf("Decodificando Mensagem...\n");

    int chave_letra_codificada;
    char letra_resultante;

    while (fscanf(MensagemEntrada, "%d", &chave_letra_codificada) != EOF) {
        if (chave_letra_codificada == -1)
            fprintf(MensagemSaida, " ");
        else {
            letra_resultante = encontra_letra_arquivo_chaves(ArquivoChaves, chave_letra_codificada);
            fprintf(MensagemSaida, "%c", letra_resultante);
        }
    }

    fclose(MensagemSaida);
    fclose(MensagemEntrada);
    fclose(ArquivoChaves);

	printf("Mensagem decodificada!\n");

    return;
}

char encontra_letra_lista (fila_t *f, int chave_letra_requerida) {

    char letra;

    nodo_f_t *aux = f->ini;

    for (int i = 0; i < tamanho_fila(f); i++){
        letra = aux->letra;

        for (int j = 0; j < aux->tamanho; j++) {
            if (chave_letra_requerida == aux->chaves[j])
                return letra;
        }
        aux = aux->prox;
    }

    return ' ';
}

void decodifica_mensagem_livro (FILE *LivroCifra, FILE *MensagemSaida, FILE *MensagemEntrada) {
	printf("Decodificando Mensagem...\n");

    fila_t *f = cria_lista_encode(LivroCifra);

    int chave_letra_codificada;
    char letra_resultante;

    while (fscanf(MensagemEntrada, "%d", &chave_letra_codificada) != EOF) {
        if (chave_letra_codificada == -1)
            fprintf(MensagemSaida, " ");
        else {
            letra_resultante = encontra_letra_lista(f, chave_letra_codificada);
            fprintf(MensagemSaida, "%c", letra_resultante);
        }
    }

    fclose(LivroCifra);
    fclose(MensagemEntrada);
    fclose(MensagemSaida);

	printf("Mensagem decodificada!\n");

    return;
}