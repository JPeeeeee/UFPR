#include <stdio.h>

typedef enum { APROVADO, FINAL, REPROVADO } resultado_t;

int main() {
    int nota, frequencia;

    resultado_t resultado;

    printf("Digite a sua nota:");
    scanf("%d" &nota);

    printf("Digite a sua frequencia:");
    scanf("%d" &frequecia);

    if (frequecia < 75){
        resultado = REPROVADO;
    } else if (nota < 40) {
        resultado = REPROVADO;
    } else if (nota < 70){
        resultado = FINAL;
    }

    return 0;
}