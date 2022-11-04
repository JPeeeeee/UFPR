#include <stdio.h>
#include <stdlib.h>

int PesquisaBinaria(int vet[], int elem, int TAM){
	int esquerda, direita;

	esquerda = 0;
	direita = TAM - 1;
	
	do{
		int meio = (esquerda + direita)/2;

		if (elem > vet[meio]) 
			esquerda = meio + 1;
		else
			direita = meio - 1;

		if (elem == vet[meio])	
			return meio;

	} while(esquerda <= direita);
}

int main (){
	int x;
	int vet[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	printf("Insira o elemento a ser procurado:\n");
	scanf("%d", &x);

	for (int i = 0; i < 10; i++)
		printf("%d  ", vet[i]);

	int res = PesquisaBinaria(vet, x, 10);
	printf("res = %d\n", res);

	if (vet[res] == x)
		printf("%d Encontrado!\n", vet[res]);
	else
		printf("Nao encontrei!\n");

	return 0;
}

