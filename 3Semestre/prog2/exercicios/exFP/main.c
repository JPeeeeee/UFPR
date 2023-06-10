#include <stdio.h>
#include <stdlib.h>

struct number {
    int num;
};
typedef struct number number_t;

int compareInt ( const void *x, const void *y ){
    int *a = (int *) x;
    int *b = (int *) y;

    if (*a > *b) return 1;
    if (*a == *b) return 0;
    if (*a < *b) return -1;
}

int compareDouble ( const void *x, const void *y ){
    double *a = (double *) x;
    double *b = (double *) y;

    if (*a > *b) return 1;
    if (*a == *b) return 0;
    if (*a < *b) return -1;
}

int compareStruct ( const void *x, const void *y ){
    number_t *a.num = (number_t *) x;
    number_t *b.num = (number_t *) y;

    if (*a > *b) return 1;
    if (*a == *b) return 0;
    if (*a < *b) return -1;
}

int main () {

    int vetor[100], i;
    double vetor_d[100];
    number_t vetor_s[100];

    srand(13);

    for (i = 0; i < 100; i++) {
        vetor[i] = rand() % 100;
        vetor_d[i] = rand() % 100;
        vetor_s.num = rand() % 100;
    }

    
    qsort(vetor, 100, sizeof(int), compareInt);
    qsort(vetor, 100, sizeof(int), compareDouble);
    qsort(vetor, 100, sizeof(int), compareStruct);


    printf("vetor de int: \n")
    for (i = 0; i < 100; i++) {
        printf("%d ", vetor[i]);
    }
    printf("\n");
    printf("vetor de double: \n")
    for (i = 0; i < 100; i++) {
        printf("%d ", vetor_d[i]);
    }
    printf("\n");

    printf("vetor de struct: \n")
    for (i = 0; i < 100; i++) {
        printf("%d ", vetor_s.num[i]);
    }
    printf("\n");

    return 0;
}