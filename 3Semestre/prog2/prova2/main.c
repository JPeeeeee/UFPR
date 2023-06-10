#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef enum { NOP, ENCODE, DECODE } Modo_t;

#define BUFFER_SIZE 10

// PROTÓTIPOS

// Função que comprime 'fIn', gravando o resultado da compressão em 'fOut'
void Encode (char *fIn, char *fOut);

// Função que descomprime 'fIn', gravando o resultado da descompressão em 'fOut'
void Decode (char *fIn, char *fOut);

// Função  ser  usada  no  programa para  chamar  Encode()  ou  Decode()
void rle (Modo_t modo, char* fIn, char* fOut);


// PROGRAMA PRINCIPAL
int main(int argc, char *argv[])
{

  int opt;
  char *input = NULL;
  char *output = NULL;
  Modo_t modo = NOP;
  
  while ((opt = getopt(argc, argv, "dei:o:")) != -1) {
    switch (opt) {
    case 'i':
      input = strdup(optarg);
      break;
    case 'o':
      output = strdup(optarg);
      break;
    case 'e':
      modo |= ENCODE;
      break;
    case 'd':
      modo |= DECODE;
      break;
    default:
      fprintf(stderr, "Forma de uso: ./rle [-e | -d] -i <arq_in> -o <arq_out>\n");
      exit(1);
    }		
  }

  // Erro se:
  //  * não forneceu os dois arquivos
  //  * não forneceu uma das opções '-e' ou '-d',
  //  * forneceu as opções '-e' e '-d' na mesma linha de comando
  if ( ! input || ! output || modo == NOP || modo & (modo-1) ) {
    fprintf(stderr, "Forma de uso: ./rle [-e | -d] -i <arq_in> -o <arq_out>\n");
    exit(2);
  }
  
  rle(modo, input, output);

  return 0 ;

}


/* DEFINA ABAIXO O CÓDIGO DAS FUNÇÕES Encode(), Decode() e rle()  */

// Função ser usada no programa principal para chamar Encode() ou Decode()
void rle (Modo_t modo, char* fIn, char* fOut)
{

  void (*fp) (char *, char *);

  switch (modo) {
    case ENCODE:
      fp = Encode;
      fp(fIn, fOut);
      break;
    case DECODE: 
      fp = Decode;
      fp(fIn, fOut);
      break;
    default:
      break;
  }
}



// Função que comprime 'fIn', gravando o resultado da compressão em 'fOut'
void Encode (char *fIn, char *fOut)
{
  FILE * arq_in;
  FILE * arq_out;

  arq_in = fopen(fIn, "r");
  arq_out = fopen(fOut, "w");

  char buff_write[BUFFER_SIZE];
  char c, c_aux;
  int counter, i_write;

  if (!arq_in || !arq_out){
    printf("erro!\n");
    return;
  }

  i_write = 0;

  while (!feof(arq_in)) {
    c_aux = c;

    fread(&c, sizeof(char), 1, arq_in);

    if (c != c_aux){
      if (i_write < BUFFER_SIZE){
        buff_write[i_write] = counter;
        i_write++;
        buff_write[i_write] = c;
        i_write++;
      } else {
        fwrite(buff_write, sizeof(char), BUFFER_SIZE, arq_out);
        printf("%s", buff_write);
        i_write = 0;
      }
    }
    counter++;
  }
}



// Função que descomprime 'fIn', gravando o resultado da descompressão em 'fOut'
void Decode (char *fIn, char *fOut)
{
  FILE * arq_in;
  FILE * arq_out;

  arq_in = fopen(fIn, "r");
  arq_out = fopen(fOut, "w");

}

