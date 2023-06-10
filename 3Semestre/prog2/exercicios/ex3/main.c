#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #define VOGAIS "aeiou"

typedef struct {
    unsigned int letra: 5;
    unsigned int vogal: 1;
    unsigned int maiuscula: 1;
    unsigned int depoisM: 1;
    unsigned int alphaBeta: 1; // retorna 1 caso a letra seja primeira ou ultima e 0 caso contrario
    unsigned int vizinho: 1;
    unsigned int tilTheEnd: 5;
} bit_t;

int xekaVogal(char c){

    const VOGAIS = "aeiou";

    for (int i = 0; i < 5; i++){
        if (toLower(c) == VOGAIS[i]) {
            return 1;
        }
    }

    return 0;
}

int main () {

    bit_t data;
    char caractere;

    scanf("%c", &caractere);

    if (caractere >= 65 && caractere <= 90) {
        data.letra = caractere - 65;

        if (xecaVogal(caractere))

    } else if (caractere >= 97 && caractere <= 122){
        data.letra = caractere - 97;
        
    }

    return 0;
}