#include <stdio.h>
#include <stdlib.h>

void troca(int vet[], int i, int j){
    int aux = vet[i];
    vet[i] = vet[j];
    vet[j] = aux;
}

int particiona(int vet[], int esq, int dir) {
    int meio = (esq + dir) / 2;
    int mediana; 
    if (vet[esq] < vet[meio]) {
        if (vet[meio] < vet[dir]) {
            mediana = meio;
        } else {
            if (vet[esq] < vet[dir]) {
                mediana = dir;
            } else {
                mediana = esq;
            }
        }
    } else {
        if (vet[dir] < vet[meio]) {
            mediana = meio;
        } else {
            if (vet[dir] < vet[esq]) {
                mediana = dir;
            } else {
                mediana = esq;
            }
        }
    }

    troca(vet, mediana, dir);
        
    int pivo = vet[dir];
    int i = esq - 1;
    for (int j = esq; j <= dir - 1; j++) {
        if (vet[j] <= pivo) {
            i++;
            troca(vet, i, j);
        }
    }
    troca(vet, i + 1, dir);

    return i + 1; 
}

void quicksort(int vet[], int esq, int dir){
    if (esq < dir){
        int pivo = particiona(vet, esq, dir);
        quicksort(vet, esq, pivo - 1);
        quicksort(vet, pivo + 1, dir);
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

    quicksort(vet, 0, TAM-1);

    printf("\n===============================\n");
    printf("vetor ordenado\n");

    for (int i = 0; i < TAM; i++)
        printf("%d  ", vet[i]);
    
    printf("\n");
    return 0;
}
