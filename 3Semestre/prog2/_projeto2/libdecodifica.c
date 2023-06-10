#include <stdio.h>
#include "libdecodifica.h"
#include "libarquivochaves.h"

// le o arquivo de chaves e verifica a existencia do numero referente a letra procurada
char encontra_letra_arquivo_chaves(FILE *ArquivoChaves, int chave_letra_requerida) { 

    // garante que a leitura do arquivo comecara do lugar certo
    rewind(ArquivoChaves);

    char letra, espaco;
    int numero;

    // enquanto nao for o fim do arquivo...
    // guarda a letra atual na variavel letra
    while (fscanf(ArquivoChaves, "%c:", &letra) != EOF) {

        // le os espacos entre as chaves e guarda na variavel espaco
		espaco = fgetc(ArquivoChaves);
        fscanf(ArquivoChaves, "%d", &numero);

        // enquanto as chaves lidas ainda forem da mesma letra, compara a chave com o inteiro passado para a funcao
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

// funcao que gerencia as operacoes necessarias para decodificar a mensagem
// utilizando o arquivo de chaves
void decodifica_mensagem_chaves(FILE *ArquivoChaves, FILE *MensagemSaida, FILE *MensagemEntrada) {
	printf("Decodificando Mensagem...\n");

    int chave_letra_codificada;
    char letra_resultante;

    // le a mensagem codificada
    // caso o numero seja -1, imprime um espaco
    // caso seka -2, imprime uma quebra de linha
    // por fim, busca no arquivo de chaves o numero 
    // requerido e imprime a letra referente a chave, se ela existir
    while (fscanf(MensagemEntrada, "%d", &chave_letra_codificada) != EOF) {
        if (chave_letra_codificada == -1)
            fprintf(MensagemSaida, " ");
        else if (chave_letra_codificada == -2)
            fprintf(MensagemSaida, "\n");
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


// utiliza a estrutura fila para verificar a existencia do numero 
// referente a letra procurada e, caso encontrada, retorna a letra
char encontra_letra_lista (fila_t *f, int chave_letra_requerida) {

    char letra;

    nodo_f_t *aux = f->ini;

    // itera por cada um dos nodos da fila
    for (int i = 0; i < tamanho_fila(f); i++){
        letra = aux->letra;
        
        // compara cada um dos elementos do vetor com a chave e, em caso positivo
        // retorna a letra do nodo
        for (int j = 0; j < aux->tamanho; j++) {
            if (chave_letra_requerida == aux->chaves[j])
                return letra;
        }
        aux = aux->prox;
    }

    return ' ';
}


// funcao que gerencia as operacoes necessarias para decodificar a 
// mensagem utilizando um livro cifra
void decodifica_mensagem_livro (FILE *LivroCifra, FILE *MensagemSaida, FILE *MensagemEntrada) {
	printf("Decodificando Mensagem...\n");

    fila_t *f = cria_lista_encode(LivroCifra);

    int chave_letra_codificada;
    char letra_resultante;

    // le a mensagem codificada
    // caso o numero seja -1, imprime um espaco
    // caso seka -2, imprime uma quebra de linha
    // por fim, busca no na fila o numero requerido e 
    // imprime a letra referente a chave, se ela existir
    while (fscanf(MensagemEntrada, "%d", &chave_letra_codificada) != EOF) {
        if (chave_letra_codificada == -1)
            fprintf(MensagemSaida, " ");
        else if (chave_letra_codificada == -2)
            fprintf(MensagemSaida, "\n");
        else {
            letra_resultante = encontra_letra_lista(f, chave_letra_codificada);
            fprintf(MensagemSaida, "%c", letra_resultante);
        }
    }

    destroi_fila(f);

    fclose(LivroCifra);
    fclose(MensagemEntrada);
    fclose(MensagemSaida);

	printf("Mensagem decodificada!\n");

    return;
}