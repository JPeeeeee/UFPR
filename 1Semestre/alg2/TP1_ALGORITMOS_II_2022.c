#include <stdio.h>
#include <stdlib.h>

/* Funcao troca que sera usada em alguns algoritmos */
void troca(int vet[], int a, int b) {
  int aux = vet[a];
  vet[a] = vet[b];
  vet[b]= aux;
}

void imprimeVetor(int vet[], int TAM){
	for (int i = 0; i < TAM; i++)
		printf("%d  ", vet[i]);
}

/* Algoritmo SelectSort */
void SelectSort(int vet[], int TAM){
	int i;
	int inspecoes = 0;
    for (int passo = 0; passo < TAM - 1; passo++){
        int min = passo;
        for (i = passo + 1; i < TAM; i++){
            if (vet[i] < vet[min])
                min = i;
			inspecoes++;
        }
        troca(vet, min, passo);
    }
	printf("Fiz %d inspecao(oes) ate que o vetor fosse ordenado\n", inspecoes);
}   


/* Algoritmo particiona para QuickSort */
int particiona(int vet[], int esq, int dir, int *inspecoes_temp){
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
		*inspecoes_temp += 1;
        if (vet[j] <= pivo) {
            i++;
            troca(vet, i, j);
        }
    }
    troca(vet, i + 1, dir);
    return i + 1;
}

/* Algoritmo QuickSor recursivo */
void quickSort(int vet[], int esq, int dir, int *inspecoes){
	int inspecoes_temp = 0;
    if (esq < dir){
        int pivo = particiona(vet, esq, dir, &inspecoes_temp);
		*inspecoes += inspecoes_temp;
        quickSort(vet, esq, pivo - 1, &inspecoes_temp);
        quickSort(vet, pivo + 1, dir, &inspecoes_temp);
    }
}

/* Algoritmo QuickSort iterativo */
void QuickSortIterativo(int Vetor[], int Esquerda, int Direita, int *inspecoes){
	int Posicao, Pilha[Direita + 1], top;
	int inspecoes_temp = 0;

	top = -1;
	Pilha[++top] = Esquerda;
	Pilha[++top] = Direita;
	while (top >= 0){
		Direita = Pilha[top--];
		Esquerda = Pilha[top--];

		Posicao = particiona(Vetor, Esquerda, Direita, &inspecoes_temp);

		if (Posicao-1 > Esquerda){
				Pilha[++top] = Esquerda;
				Pilha[++top] = Posicao - 1;
		}

		if (Posicao+1 < Direita){
				Pilha[++top] = Posicao + 1;
				Pilha[++top] = Direita;
		}
	}
	*inspecoes = inspecoes_temp;
}

/* Algoritmo BubbleSort */
void bubbleSort(int vet[], int TAM){
    int i, j;
	int inspecoes;

	for (i = 0; i < TAM - 1; i++)
		for (j = 0; j < TAM - i - 1; j++)
			if (vet[j] > vet[j + 1]){
				inspecoes++;
				troca(vet, j, j + 1);
			}
	printf("Fiz %d inspecao(oes) ate que o vetor fosse ordenado\n", inspecoes);
}

/* Algoritmo pesquisa binária */
int PesquisaBinaria(int vet[], int elem, int TAM){
	int esquerda, direita, inspecoes;

	esquerda = 0;
	direita = TAM - 1;
	inspecoes = 0;

	while(esquerda <= direita){
		int meio = (esquerda + direita)/2;
		inspecoes++;

		if (elem > vet[meio]) 
			esquerda = meio + 1;
		else
			direita = meio - 1;

		if (elem == vet[meio]){
			printf("Fiz %d inspecao(oes).\n", inspecoes);
			return meio;
		}
	} 

	printf("Fiz %d inspecao(oes).\n", inspecoes);
	return -1;
}


/* Algoritmo pesquisa sequencial */
int PesquisaSequencial(int vet[], int Elem, int TAM) {
	int i, inspecoes;

	for (i = 0; i < TAM; i++) {
		inspecoes++;
		if (vet[i] == Elem){
			printf("Fiz %d inspecao(oes).\n", inspecoes);
			return i;
		}
	}

	printf("Fiz %d inspecao(oes).\n", inspecoes);
	return -1; 
}

/* Funcao que define se um numero foi sorteado ou nao. */
int acertou(int vet[], int acertou_elem){
	if (acertou_elem != -1){
		printf("Numero %d encontrado!\n", vet[acertou_elem]);
		return 1;
	} else
		printf("Numero nao sorteado.\n");
	return 0;
}

void megaQuadra(){
    int TAM, max, indicador, a, b, c, d;

	/* Inicio do jogo MEGA QUADRA */

    printf("======================================================\n");
    printf("             BEM VINDO(E) A MEGA QUADRA!\n");
    printf("======================================================\n");

    printf("Insira o tamanho do vetor: \n");
    scanf("%d", &TAM);

	printf("Qual eh o valor maximo do vetor?: \n");
    scanf("%d", &max);

	printf("Insira seus 4 numeros da sorte: \n");
    scanf("%d %d %d %d", &a, &b, &c, &d);
    printf("======================================================\n");

	/* Define cada valor do vetor de forma aleatoria */

    int vet[TAM];
	for (int i = 0; i < TAM; i++)
        vet[i] = rand() % max;
    

	/* Pergunta se quer mostrar o vetor. Se sim, chama a funcao imprimeVetor. */
	printf("                   Vetor criado!\n");
	printf("Exibir vetor?\n1. Sim\n2. Nao\n");
	scanf("%d", &indicador);

	if (indicador == 1){
		printf("Vetor original:\n");
		imprimeVetor(vet, TAM);
		printf("\n");
	} 

	/* Define qual algoritmo de ordenacao sera utilizado para o vetor criado anteriormente. */
	int escolher_ordenacao = 0;
	while (escolher_ordenacao != 1){
		printf("======================================================\n");
		printf("Qual algoritmo de ordenacao voce prefere?\n1. SelectSort\n2. BubbleSort\n3. QuickSort recursivo\n4. QuickSort iterativo\n");
		scanf("%d", &indicador);

		int inspecoes = 0;

		switch (indicador){
			case 1:
				SelectSort(vet, TAM);
				escolher_ordenacao = 1;
				break;

			case 2:
				bubbleSort(vet, TAM);
				escolher_ordenacao = 1;
				break;

			case 3:
				quickSort(vet, 0, TAM - 1, &inspecoes);
				printf("Fiz %d inspecao(oes) ate que o vetor fosse ordenado\n", inspecoes);
				escolher_ordenacao = 1;
				break;

			case 4:
				QuickSortIterativo(vet, 0, TAM - 1, &inspecoes);
				printf("Fiz %d inspecao(oes) ate que o vetor fosse ordenado\n", inspecoes);
				escolher_ordenacao = 1;
				break;

			default:
				printf("Insira um numero valido!\n");
				break;
		}
	}
    printf("Vetor ordenado!\n");
	imprimeVetor(vet, TAM);

    printf("\n======================================================\n");

	/* 
		Abre uma escolha para o usuario. Dessa forma, sera possivel ver como o 
		vetor foi ordenado antes de mostrar os resultados do sorteio.
	*/

	int sortear = 0;
	while (sortear != 1){
		printf("Para analisar se os numeros da sorte foram sorteados digite 1.\n");
		scanf("%d", &sortear);
	} 

	printf("Analisando se seus numeros foram sorteados...\n");

	int acertou_a, acertou_b, acertou_c, acertou_d;

	printf("-------------------------------------------------------\n");
	printf("                   Pesquisa Binaria\n");
	printf("-------------------------------------------------------\n");

	/* Procurando os valores A, B, C e D no vetor com pesquisa binaria */
	int acertos_binaria = 0;

	acertou_a = PesquisaBinaria(vet, a, TAM);
	acertos_binaria += acertou(vet, acertou_a);
	
	printf("------------------------\n");

	acertou_b = PesquisaBinaria(vet, b, TAM);
	acertos_binaria += acertou(vet, acertou_b);

	printf("------------------------\n");

	acertou_c = PesquisaBinaria(vet, c, TAM);
	acertos_binaria += acertou(vet, acertou_c);

	printf("------------------------\n");

	acertou_d = PesquisaBinaria(vet, d, TAM);
	acertos_binaria += acertou(vet, acertou_d);

	printf("-------------------------------------------------------\n");
	printf("                   Pesquisa Sequencial\n");
	printf("-------------------------------------------------------\n");

	/* Procurando os valores A, B, C e D no vetor com pesquisa sequencial */
	int acertos_sequencial = 0;

	acertou_a = PesquisaSequencial(vet, a, TAM);
	acertos_sequencial += acertou(vet, acertou_a);
	
	printf("------------------------\n");

	acertou_b = PesquisaSequencial(vet, b, TAM);
	acertos_sequencial += acertou(vet, acertou_b);
	
	printf("------------------------\n");

	acertou_c = PesquisaSequencial(vet, c, TAM);
	acertos_sequencial += acertou(vet, acertou_c);
	
	printf("------------------------\n");

	acertou_d = PesquisaSequencial(vet, d, TAM);
	acertos_sequencial += acertou(vet, acertou_d);
	
	printf("\n======================================================\n");

	if (acertos_sequencial != 0 || acertos_binaria != 0){	
		printf("Segundo a pesquisa binaria foram sorteados %d numeros! Parabéns!!!\n", acertos_binaria);
		printf("Segundo a pesquisa sequencial foram sorteados %d numeros! Parabens!!!\n", acertos_sequencial);
    	printf("======================================================\n");
	} else{
		printf("Nenhum dos numeros da sorte foram sorteados :(\n");
	}
}


int main(){
	int i;

	megaQuadra();

	/* Pergunta ao usuario se ele gostaria de jogar novamente. */
	while (i != 2){
    	printf("Jogar novamente?\n1. Sim\n2. Nao\n");
		scanf("%d", &i);

		if (i == 1)
			megaQuadra();
		else if (i != 2){
			printf("Insira um numero valido!\n");
			scanf("%d", &i);
		}
	}

    return 0;
}
