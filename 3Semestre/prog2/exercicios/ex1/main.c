#include <stdio.h>
#include <string.h>
#define TAM 255

int main() {
    char string[TAM];

    scanf("%s", string);
    
    for (int i = strlen(string); i >= 0; i--){
        printf("%c", string[i]);
    }

    printf("\n");

    return 0;
}