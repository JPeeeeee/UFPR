#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// para garantir que os valores apagados nao irao interferir no 
// algoritmo da tabela, foram definidos 3 estados para cada posicao de ambas as tabelas
// VAZIO, APAGADO e OCUPADO
#define VAZIO 0
#define APAGADO 1
#define OCUPADO 2

#define TAM 11 


// estrutura para cada elemento da tabela
typedef struct valor_hash{
    int chave;
    int estado;
} valor_hash_t;


// estrutura de tabelas
typedef struct cuc_hash{
    valor_hash_t *T1;
    valor_hash_t *T2; 
} cuc_hash_t; 

cuc_hash_t *init_hash(){
    cuc_hash_t *novo_cuc_hash = malloc(sizeof(cuc_hash_t));

    novo_cuc_hash->T1 = malloc(sizeof(valor_hash_t) * TAM);
    novo_cuc_hash->T2 = malloc(sizeof(valor_hash_t) * TAM);

    return novo_cuc_hash;
}

int h1(int k){
    return (k % TAM);
}

int h2(int k){
    return floor(TAM * (k * 0.9 - floor(k * 0.9)));
}

// busca um valor nas tabelas hash e retorna em qual das duas tabelas ele esta
int busca_hash(cuc_hash_t *T, int k){
    int i;

    i = h1(k);

    if (T->T1[i].estado == APAGADO){
        i = h2(k);
        if (T->T2[i].chave == k)
            return 2;
    } else if(T->T1[i].chave == k) {
        return 1;
    } else {
        i = h2(k);
        
        if (T->T2[i].chave == k)
            return 2;
    }

    return 0;
}


// insere o valor na tabela hash respeitando a propriedade do CuckooHash
int inserir_hash(cuc_hash_t *T, int k){
    int i, j;


    if (busca_hash(T, k))
        return -1;

    i = h1(k);

    if (T->T1[i].estado == VAZIO || T->T1[i].estado == APAGADO){

        T->T1[i].chave = k;    
        T->T1[i].estado = OCUPADO;  

        return i;
    } else{

        j = h2(T->T1[i].chave);

        T->T2[j].chave = T->T1[i].chave;
        T->T1[i].chave = k;

        T->T2[j].estado = OCUPADO;

        return j;
    }
}

// funcao para remover valor ja existente de uma das tabelas hash
int remove_hash(cuc_hash_t *T, int k){
    int res = busca_hash(T, k);

    if (res == 0)
        return -1;

    if (res == 1){
        T->T1[h1(k)].estado = APAGADO;
        return 1;
    } else{
        T->T2[h2(k)].estado = APAGADO;
        return 1;
    }
}

// funcao para quickSort
int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

void imprime_saida_hash(cuc_hash_t *T){
    int j;
    int k = 0;

    // descobre quantos elementos existem em ambas as tabelas
    for (j = 0; j < 22; j++){
        if (j < TAM && T->T1[j].estado == OCUPADO)
            k++;
        else if (j >= TAM && T->T2[j % TAM].estado == OCUPADO)
            k++;
    }

    // aloca o tamanho do vetor de numeros nas tabelas dinamicamente
    int *res = malloc(sizeof(int) * k);

    int p = 0;

    // insere os valores das tabelas em um vetor 
    for (j = 0; j < 22; j++){
        if (j < TAM && T->T1[j].estado == OCUPADO){
            res[p] = T->T1[j].chave;
            p++;
        } else if (j >= TAM && T->T2[j % TAM].estado == OCUPADO){
            res[p] = T->T2[j % TAM].chave;
            p++;
        }
    }

    // ordena o vetor de valores
    qsort(res, k, sizeof(int), cmpfunc);

    int tabela_num;

    // imprime saida 
    for (int i = 0; i < k; i++){
        tabela_num = busca_hash(T, res[i]);

        if (tabela_num == 1)
            fprintf(stdout, "%d,T1,%d\n", res[i], h1(res[i]));
        else if (tabela_num == 2)
            fprintf(stdout, "%d,T2,%d\n", res[i], h2(res[i]));
    }
}

int main(int argc, char *argv[]){

    cuc_hash_t *T = init_hash();

    // seta todos os valores de ambas as tabelas para 0 e coloca os estados em vazio
    for (int j = 0; j < TAM; j++){
        T->T1[j].chave = 0;
        T->T2[j].chave = 0;

        T->T1[j].estado = VAZIO;
        T->T2[j].estado = VAZIO;
    }

    // le o arquivo de entrada e realiza as operacoes
    char s[10], c;
    int num_input;
    while (!feof(stdin)){
        c = fgetc(stdin);
        if (c == 'i'){
            scanf("%d", &num_input);
            inserir_hash(T, num_input);
        } else if (c == 'r'){
            scanf("%d", &num_input);
            remove_hash(T, num_input);
        }
    }

    imprime_saida_hash(T);

    return 0;
}