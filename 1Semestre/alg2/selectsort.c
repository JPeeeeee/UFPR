#include <stdio.h>
#include <stdlib.h>

void troca(int vet[], int a, int b) {
  int aux = vet[a];
  vet[a] = vet[b];
  vet[b]= aux;
}

void selectSort(int vet[], int TAM){
    for (int passo = 0; passo < TAM - 1; passo++){
        int min = passo;
        for (int i = passo + 1; i < TAM; i++){
            if (vet[i] < vet[min])
                min = i;
        }
        troca(vet, min, passo);
    }
}

int main(){
    int TAM;

    printf("insira o tamanho do vetor: \n");
    scanf("%d", &TAM);

    int vet[TAM];

    printf("===============================\n");
    printf("vetor original:\n");

    for (int i = 0; i < TAM; i++){
        vet[i] = rand() % TAM;
        printf("%d  ", vet[i]);
    }

    selectSort(vet, TAM);

    printf("\n===============================\n");
    printf("vetor ordenado\n");

    for (int i = 0; i < TAM; i++)
        printf("%d  ", vet[i]);

    printf("\n");
    return 0;
}
