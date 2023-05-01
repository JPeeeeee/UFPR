#include "libfila.h"

// Retorna o ponteiro pra estrutura lista com todas as letras e chaves
fila_t *cria_lista_encode(FILE *LivroCifra);


// Cria o arquivo de chaves a partir da lista
void gera_arquivo_chaves(FILE *ArquivoChaves, fila_t *f);