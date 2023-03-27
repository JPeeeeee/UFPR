#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <wchar.h>
#include "libfila.h"

#define BUFF 255

void coleta_dados_texto (FILE *livro_cifra, fila_t *f) {

    wchar_t palavra[BUFF];

    int p = 0;

    while (fscanf(livro_cifra, "%ls", palavra) != EOF) {
		printf("%ls, ", palavra);
		wchar_t primeira_letra;
		
		// Rever com professor
		primeira_letra = palavra[0];

		if (p == 0)
			primeira_letra = palavra[1];

		insere_fila(f, primeira_letra, p);

		p++;		
    }
}

int main(int argc, char *argv[]) {
    setlocale(LC_ALL,"");

	printf("argumento: %s\n", argv[1]);

    FILE *livro_cifra;

    fila_t *f = cria_fila();

    // Lembrar de mudar para argc
    livro_cifra = fopen("LivroCifra.txt", "r");

    if (livro_cifra == NULL)
      return -1;

	printf("Palavras: ");

	// coleta_dados_texto(livro_cifra, f);

	printf("\n");

    fclose(livro_cifra);

    nodo_f_t *aux = f->ini;
    
    for (int i = 0; i < tamanho_fila(f); i++){
		printf("%lc: ", aux->letra);

		for (int j = 0; j < aux->tamanho; j++) {
			printf("%d ", aux->chaves[j]);
		}

		printf("\n");
		aux = aux->prox;
    }
}