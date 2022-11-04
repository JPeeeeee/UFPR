#include <stdio.h>

int ehPrimo(int numero){
	int primo,contF=2;

	if (numero%2==0){
		return 1;
	} else{
		while (numero > contF && contF<10 && primo != 0){
			if (numero%contF == 0){
				return 1;
			}
			contF++;
		}
	}
	return 0;
}

int main(){
	int cont,n;
	scanf("%d", &n);

	while (cont != n)

	printf("%d\n", ehPrimo(cont));

	for (cont = 1; cont <= n; cont++){
		if (ehPrimo(cont) == 0){
			printf("%d\n", cont);
       		}
	}

	return 0;
}
