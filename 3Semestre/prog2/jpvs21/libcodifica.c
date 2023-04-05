#define BUFF 255
#include <wchar.h>
#include "libcodifica.h"

fila_t *coleta_dados_texto_fila (char *nome_arquivo_cifra) {
    FILE *livro_cifra;

    fila_t *f = cria_fila();
    
    // // Lembrar de mudar para argc
    livro_cifra = fopen("LivroCifra.txt", "r");

    if (livro_cifra == NULL)
        return NULL;

    
    printf("\n");

    
    wchar_t palavra[BUFF];

    int p = 0;

    while (fscanf(livro_cifra, "%ls", palavra) != EOF) {
        wchar_t primeira_letra;
        
        // Rever com professor
        primeira_letra = palavra[0];

        if (p == 0)
          primeira_letra = palavra[1];

        primeira_letra = tolower(primeira_letra);

        if (primeira_letra >= 97 && primeira_letra <= 122)
            insere_fila(f, primeira_letra, p);

        p++;		
    }

    fclose(livro_cifra);
  return f;
}