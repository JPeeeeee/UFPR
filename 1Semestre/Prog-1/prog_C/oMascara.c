#include <stdio.h>
#include <math.h>

int main(){
  int a, b, c, delta;
  int x1, x2;
  
  printf("Insira o valor a: \n");
  scanf("%d", &a);
  
  printf("Insira o valor b: \n");
  scanf("%d", &b);

  printf("Insira o valor c: \n");
  scanf("%d", &c);

  delta = (b*b)-(4*a*c);

  x1 = ((-b)+(sqrt(delta)))/2*a;
  x2 = ((-b)-(sqrt(delta)))/2*a;

  printf("x1: %d \nx2: %d \n", x1, x2);
}



