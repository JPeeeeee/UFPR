#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define VAZIO 0
#define APAGADO 1
#define OCUPADO 2
#define TAM 11 

typedef struct valor_hash{
    int chave;
    int estado;
} valor_hash_t;

typedef struct cuc_hash{
    valor_hash_t *T1;
    valor_hash_t *T2; 
} cuc_hash_t; 

cuc_hash_t *init_hash(){

    cuc_hash_t *novo_cuc_hash = malloc(sizeof(cuc_hash_t));

    novo_cuc_hash->T1 = malloc(sizeof(valor_hash_t) * 11);
    novo_cuc_hash->T2 = malloc(sizeof(valor_hash_t) * 11);

    return novo_cuc_hash;
}

int h1(int k){
    return (k % TAM);
}

int h2(int k){
    return floor(TAM * (k * 0.9 - floor(k * 0.9)));
}

void print(valor_hash_t *Tx){

    printf("[");

    for (int i = 0; i < 11; i++){
        if (Tx[i].estado == APAGADO || Tx[i].estado == VAZIO)
            printf("0, ");
        else
            printf("%d, ", Tx[i].chave);
    }

    printf("]");
}


int busca_hash(cuc_hash_t *T, int k){
    int i;

    i = h1(k);

    if (T->T1[i].estado == APAGADO){
        i = h2(k);
        if (T->T2[i].chave == k)
            return 2;
    } 

    else if(T->T1[i].chave == k) {
        return 1;
    } 

    else {
        i = h2(k);
        
        if (T->T2[i].chave == k)
            return 2;
    }

    return 0;
}

int inserir_hash(cuc_hash_t *T, int k){
    int i, j;

    // vetor resultado que recebe a tabela na posicao 0 e o index na posicao 1

    if (busca_hash(T, k))
        return -1;

    i = h1(k);

    if (T->T1[i].estado == VAZIO || T->T1[i].estado == APAGADO){

        T->T1[i].chave = k;    
        T->T1[i].estado = OCUPADO;  

        return i;
    } 
    
    else{

        j = h2(T->T1[i].chave);

        T->T2[j].chave = T->T1[i].chave;
        T->T1[i].chave = k;

        T->T2[j].estado = OCUPADO;

        return j;
    }
}


int remove_hash(cuc_hash_t *T, int k){
    // vetor resultado que recebe a tabela na posicao 0 e o index na posicao 1
    int res = busca_hash(T, k);

    if (res == 0)
        return -1;

    // muda o estado dos valores para apagado
    if (res == 1){
        T->T1[h1(k)].estado = APAGADO;
        return 1;
    } 
    
    else{
        T->T2[h2(k)].estado = APAGADO;
        return 1;
    }
}

void imprime_saida_hash(cuc_hash_t *T){
    for (int i = 0; i < 11; i++){
        if (T->T1[i].estado == OCUPADO){
            fprintf(stdout, "%d,T1,%d\n", T->T1[i].chave, i);   
        }
        else if (T->T2[i].estado == OCUPADO){
            fprintf(stdout, "%d,T2,%d\n", T->T2[i].chave, i);   
        }
    }
}

int main(int argc, char *argv[]){

    cuc_hash_t *T = init_hash();

    for (int j = 0; j < 11; j++){
        T->T1[j].chave = 0;
        T->T2[j].chave = 0;

        T->T1[j].estado = VAZIO;
        T->T2[j].estado = VAZIO;
    }

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

    printf("Tabela 1: ");
    print(T->T1);
    printf("\n");
    printf("Tabela 2: ");
    print(T->T2);
    printf("\n");

    return 0;
}