#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFF 255

char *get_nome (FILE *arquivo_binario){
    char *nome = NULL, c;
    int i = 0;

    fread (&c, sizeof(char), 1, arquivo_binario);
    while (c != '\n'){
        // Aparentemente existe um numero limite de reallocs no programa
        // Ao ler o nome do 3 arquivo o limite eh atingido e o programa para
        nome = realloc(nome, sizeof(char));
        nome[i] = c;
        fread (&c, sizeof(char), 1, arquivo_binario);
        i++;
    }

    return nome;
}

void le_arquivo_binario(FILE * arquivo_binario){
    char c, *nome;
    
    int quantidade_registros, tamanho_registro, value, flag_tamanho_reg, flag_nome;
    flag_tamanho_reg = 1;
    int contador_registros = 0, contador = 0, i = 0;
    
    fread (&quantidade_registros, sizeof(int), 1, arquivo_binario) ;

    // Ao trocar o valor 2 pela quantidade de registros, o programa 
    // executa um numero limite de reallocs e para o programa

    // Os reallocs acontecem dentro da funcao get_nome
    while (contador_registros < 2){ 
           
        fread (&tamanho_registro, sizeof(int), 1, arquivo_binario) ;

        nome = get_nome(arquivo_binario);

        FILE *novo_arquivo;
        novo_arquivo = fopen(nome, "w");

        // Le conteudo
        fread (&c, sizeof(char), 1, arquivo_binario);

        // Utilizando sizeof(nome) + 6 pois o sizeof(nome) nao conta a extensao,
        // portanto eh necessario adicionar mais 4 (4 char, .txt, por exemplo)
        // e mais 2 para o \n
        while (contador < tamanho_registro - (sizeof(nome) + 6)){
            fputc(c, novo_arquivo);
            fread (&c, sizeof(char), 1, arquivo_binario);
            contador++;
        }

        contador_registros++;
    }
}

void imprime_arquivo_binario(FILE * arquivo_binario){
   
    char c, *nome;
    
    int quantidade_registros, tamanho_registro, value, flag_tamanho_reg, flag_nome;
    flag_tamanho_reg = 1;
    int contador_registros = 0, contador = 0, i = 0;
    
    fread (&quantidade_registros, sizeof(int), 1, arquivo_binario) ;


    // Ao trocar o valor 2 pela quantidade de registros, o programa 
    // executa um limite de reallocs e para o programa

    // Os reallocs acontecem dentro da funcao get_nome
    while (contador_registros < 2){ 
           
        fread (&tamanho_registro, sizeof(int), 1, arquivo_binario) ;

        nome = get_nome(arquivo_binario);
        printf("nome do arquivo: %s\n", nome);

        // Le conteudo
        fread (&c, sizeof(char), 1, arquivo_binario);
        while (contador < tamanho_registro - (sizeof(nome) + 6)){
            fread (&c, sizeof(char), 1, arquivo_binario);
            contador++;
        }

        contador_registros++;
    }
}

int main(int argc, char **argv){
    FILE *arquivo_binario;

    int option;

    arquivo_binario = fopen("bkp.bin", "r");

    if (!arquivo_binario){
        printf("Erro ao abrir arquivo!");
        return -1;
    }

    while ((option = getopt (argc, argv, "t")) != -1)
        switch (option)
        {
            case 't':
                imprime_arquivo_binario(arquivo_binario);
                break;
  
            default:
                break;
        }
    
    if (argc == 1)
        le_arquivo_binario(arquivo_binario);

    
    fclose(arquivo_binario);

    return 0;
}