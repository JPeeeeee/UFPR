#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "libconjunto.h"

conjunto_t * cria_conjunto (int max){
    conjunto_t *c = malloc(sizeof(conjunto_t));

    if (c == NULL){
        free(c);
        return 0;
    }

    c->v = malloc(sizeof(int) * max);

    if (c->v == NULL){
        free(c->v);
        free(c);
        return 0;
    }

    c->max = max;
    c->ptr = 0;
    c->card = 0;

    return c;
}

conjunto_t * destroi_conjunto (conjunto_t *c){
    free(c->v);
    free(c);
    return NULL;
}

int conjunto_vazio (conjunto_t *c){
    if (c->card == 0)
        return 1;
    return 0;
}

int cardinalidade (conjunto_t *c){
    return c->card;
}

int insere_conjunto (conjunto_t *c, int elemento){
    int i;

    if (c->card >= c->max)
        return -1;
    
    if (conjunto_vazio(c)){
        c->v[c->card] = elemento;
        c->card++;
        return 1;
    }

    for (i = c->card - 1; i >= 0 ; i--){
        if (i == 0 && elemento < c->v[i]){
            c->v[i+1] = c->v[i];
            c->v[i] = elemento;
            c->card++;
            break;
        }
        
        if(elemento < c->v[i]){
            c->v[i+1] = c->v[i];
        } else{
            c->v[i+1] = elemento;
            c->card++;
            break;
        }
    }
    return 1;
}

int retira_conjunto (conjunto_t *c, int elemento){
    int i, j;
    for (i = 0; i < c->card; i++){
        if (elemento == c->v[i]){
            for (j = i; j < c->card; j++)
                c->v[j] = c->v[j+1];
            c->card--;
            return 1;
        }
    }
    return 0;
}

int pertence (conjunto_t *c, int elemento){
    int i;
    for (i = 0; i < c->card; i++)
        if (elemento == c->v[i])
            return 1;
    return 0;
}

int contido (conjunto_t *c1, conjunto_t *c2){
    int i, j;
    for (i = 0; i < c1->card; i++){
        for (j = 0; j < c2->card; j++){
            if (c1->v[i] == c2->v[j])
                break;
            if (j == c2->card - 1)
                return 0;
        }
    }
    return 1;
}

int sao_iguais (conjunto_t *c1, conjunto_t *c2){
    int i;
    if (c1->card != c2->card)
        return 0;
    for (i = 0; i < c1->card; i++)
        if (c1->v[i] != c2->v[i])
            return 0;
    return 1;
}


conjunto_t * cria_diferenca (conjunto_t *c1, conjunto_t *c2){
    int i, j;

    conjunto_t *novo = cria_conjunto(c1->card);
    conjunto_t *aux = cria_conjunto(c2->card);
    
    if (novo == NULL)
        return 0;

    for (i = 0; i < c2->card; i++){
        aux->v[i] = c2->v[i];
        aux->card++;
    }

    for (i = 0; i < c1->card; i++){
        novo->v[i] = c1->v[i];
        novo->card++;
    }

    for (i = 0; i < c1->card; i++){
        for (j = 0; j < aux->card; j++){
            if (c1->v[i] == aux->v[j]){
                retira_conjunto(aux, c1->v[i]);
                retira_conjunto(novo, c1->v[i]);
                break; 
            }
        }
    }

    return novo;
}

conjunto_t * cria_interseccao (conjunto_t *c1, conjunto_t *c2){
    conjunto_t *novo = cria_conjunto(c1->card);
    int i, j;
    int k = 0;

    if (novo == NULL)
        return 0;

    for (i = 0; i < c1->card; i++){
        for (j = 0; j < c2->card; j++){
            if (c1->v[i] == c2->v[j]){
                novo->v[k] = c1->v[i];
                novo->card++;
                k++;
                break;
            }
        }
    }

    return novo;
}


conjunto_t * cria_uniao (conjunto_t *c1, conjunto_t *c2){
    conjunto_t *novo = cria_conjunto(c1->card + c2->card);
    int i;

    for (i = 0; i < c1->card; i++)
        insere_conjunto(novo, c1->v[i]);
    for (i = 0; i < c2->card; i++)
        insere_conjunto(novo, c2->v[i]);
    
    return novo;
}

conjunto_t * cria_copia (conjunto_t *c){
    conjunto_t *novo = cria_conjunto(c->card);

    int i;
    for (i = 0; i < c->card; i++){
        novo->v[i] = c->v[i];
        novo->card++;
    }

    return novo;
}

conjunto_t * cria_subconjunto (conjunto_t *c, int n){
    conjunto_t *novo = cria_conjunto(c->card);
    conjunto_t *aux = cria_copia(c);
    time_t t;
    int i;
    srand((unsigned) time(&t));

    if ( c->v == NULL) {
        novo->v = NULL;
    } else if (n == c->card){
        return c;
    } else{
        for (i = 0; i < n; i++){
            int index = rand() % aux->card - 1;

            while (index == -1)
                index = rand() % aux->card - 1;

            novo->v[i] = aux->v[index];
            novo->card++;
            retira_conjunto(aux, novo->v[i]);
        }
    }

    return novo;
}

void imprime (conjunto_t *c){
    int i;
    for(i = 0; i < c->card; i++)
        printf("%d  ", c->v[i]);
    printf("\n");
}

int redimensiona (conjunto_t *c){
    conjunto_t *aux = cria_copia(c);

    c->max *= 2;
    free(c->v);
    c->v = malloc(sizeof(int) * c->max);

    if (c->v == NULL)
        return 0;

    int i;
    for (i = 0; i < aux->card; i++)
        c->v[i] = aux->v[i];
    destroi_conjunto(aux);

    return 1;
}

void iniciar_iterador (conjunto_t *c){
    c->ptr = 0;
}

int incrementar_iterador (conjunto_t *c, int *elemento){
    if (c->ptr >= c->max - 1)
        return 0;
    c->ptr++;
    return c->v[c->ptr];
}

int retirar_um_elemento (conjunto_t *c){
    int i;
    for (i = c->ptr; i < c->card; i++){
        c->v[i] = c->v[i+1];
        c->card--;
        return 1;
    }
    return 0;
}