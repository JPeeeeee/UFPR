#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef enum { VAZIO, APAGADO, OCUPADO } estado_t;

typedef struct valor_hash{
    int chave;
    estado_t estado;
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

int h1(int k, int m){
    return (k % m);
}

int h2(int k, int m){
    return floor(m * (k * 0.9 - floor(k * 0.9)));
}

void print(valor_hash_t *Tx){

    printf("[");

    for (int i = 0; i < 11; i++){
        if (Tx[i].estado == APAGADO)
            printf("0, ");
        else
            printf("%d, ", Tx[i].chave);
    }

    printf("]");
}


int busca_hash(cuc_hash_t *T, int k, int res[2]){
    int i;

    i = h1(k, 11);

    if (T->T1[i].estado == APAGADO){
        i = h2(k, 11);
        
        if (T->T2[i].chave == k){
            res[0] = 2;
            res[1] = i;
            return 1;
        }
    } else if(T->T1[i].chave == k){
        res[0] = 1;
        res[1] = i;
        return 1;
    } else{
        i = h2(k, 11);
        
        if (T->T2[i].chave == k){
            res[0] = 2;
            res[1] = i;
            return 1;
        }
    }
    return 0;
}

int inserir_hash(cuc_hash_t *T, int k){
    int i, j;
    int res[2];

    if (busca_hash(T, k, res)){
        return -1;
    }

    i = h1(k, 11);

    if (T->T1[i].estado == VAZIO || T->T1[i].estado == APAGADO){
        T->T1[i].chave = k;    
        T->T1[i].estado = OCUPADO;    
        return i;
    } else{

        j = h2(T->T1[i].chave, 11);

        T->T2[j].chave = T->T1[i].chave;
        T->T1[i].chave = k;

        T->T2[j].estado = OCUPADO;

        return j;
    }
}


int remove_hash(cuc_hash_t *T, int k){
    int res[2];

    // Deu ruim
    if (!busca_hash(T, k, res))
        return -1;

    if (res[0] == 1){
        T->T1[res[1]].estado = APAGADO;
        return 1;
    } else{
        T->T2[res[1]].estado = APAGADO;
        return 1;
    }
}

int main(){
    cuc_hash_t *T = init_hash();

    for (int j = 0; j < 11; j++){
        T->T1[j].chave = 0;
        T->T2[j].chave = 0;

        T->T1[j].estado = VAZIO;
        T->T2[j].estado = VAZIO;
    }

    inserir_hash(T, 1);
    inserir_hash(T, 2);
    remove_hash(T, 1);
    remove_hash(T, 2);


    printf("Tabela 1: ");
    print(T->T1);
    printf("\n");
    printf("Tabela 2: ");
    print(T->T2);
    printf("\n");

    // printf("buscando 15... ");
    // int r = busca_hash(T1, T2, 14);
    // if (r != -1)
    //     printf("encontrou!!!\nindex: %d\n", r);
    // else    
    //     printf("deu ruim kk\n");

    return 0;
}