#include "libfila.h"

// funcao que gerencia as operacoes necessarias para decodificar a mensagem
// utilizando o arquivo de chaves
void decodifica_mensagem_chaves (FILE *ArquivoChaves, FILE *MensagemSaida, FILE *MensagemEntrada);

// funcao que gerencia as operacoes necessarias para decodificar a 
// mensagem utilizando um livro cifra
void decodifica_mensagem_livro (FILE *LivroCifra, FILE *MensagemSaida, FILE *MensagemEntrada);