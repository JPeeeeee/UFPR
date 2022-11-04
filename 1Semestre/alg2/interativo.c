#include <stdio.h>
#include <stdlib.h>

void troca(int vet[], int a, int b) {
  int aux = vet[a];
  vet[a] = vet[b];
  vet[b]= aux;
}

int particiona(int vet[], int esq, int dir) {
    int meio = (esq + dir) / 2;
    int mediana;

	/* Algoritmo para encontrar a mediana entre os 3 elementos (esquerda, direita e meio) */
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

	/* Coloca a mediana na posicao mais a direita do vetor para que ela possa ser usada como pivo. */
    troca(vet, mediana, dir);

    int pivo = vet[dir];
    int i = esq - 1;
	int j;
    for (j = esq; j <= dir - 1; j++) {
        if (vet[j] <= pivo) {
            i++;
            troca(vet, i, j);
        }
    }
    troca(vet, i + 1, dir);
    return i + 1;
}

void QuickSortIterativo (int Vetor[], int Esquerda, int Direita, int TAM){
	int Posicao;
	int Pilha[TAM];
	int top;

	top = -1;
	Pilha[++top] = Esquerda;
	Pilha[++top] = Direita;
	while (top >= 0){
		Direita = Pilha[top--];
		Esquerda = Pilha[top--];

		Posicao = particiona(Vetor, Esquerda, Direita);

		if (Posicao-1 > Esquerda){
			Pilha[++top] = Esquerda;
			Pilha[++top] = Posicao - 1;
        	}

		if (Posicao+1 < Direita){
        		Pilha[++top] = Posicao + 1;
        	    	Pilha[++top] = Direita;
        	}
    	}
}

void imprimeVetor(int vet[], int TAM){
	for (int i = 0; i < TAM; i++)
		printf("%d  ", vet[i]);
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

    QuickSortIterativo(vet, 0, TAM - 1, TAM);

    printf("\n===============================\n");
    printf("vetor ordenado\n");

    for (int i = 0; i < TAM; i++)
        printf("%d  ", vet[i]);

    printf("\n");
    return 0;
}
