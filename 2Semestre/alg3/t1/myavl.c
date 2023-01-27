/*
    Trabalho realizado por: 
    Brenda Pinheiro Ricci (bpr21)
                e 
    Joao Pedro Vieira Santos (jpvs21)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct nodo{
    int chave;
    int bal;
    struct nodo *esq;
    struct nodo *dir;
};
typedef struct nodo nodo_t;

// retorna o máximo de dois números
int max(int a, int b){
	if (a>b) 
    	return a;
	return b;
}

// cria uma nova instancia da struct nodo
nodo_t *criaNodo(int chave){
  nodo_t *novoNo = (nodo_t*)malloc(sizeof(nodo_t));
  novoNo->esq = NULL;
  novoNo->dir = NULL;
  novoNo->chave = chave;
  novoNo->bal = 0;
  return novoNo;
}

// calcula e retorna a altura da arvore 
int alturaArvore(nodo_t* p){
	if (p == NULL) 
    	return -1;
	return max(alturaArvore(p->esq),alturaArvore(p->dir)) + 1;
}

// imprime os valores da árvore em ordem crescente
void emOrdem(nodo_t* raiz){
	if (raiz == NULL) 
    return;
	emOrdem(raiz->esq);
	printf("%i ",raiz->chave);
	emOrdem(raiz->dir);
}

// imprime a raiz da arvore, e seus filhos da esqueda e direita respectivamente.
void preOrdem(nodo_t* raiz){
	if (raiz == NULL) 
    return;
	printf("%i ",raiz->chave);
	preOrdem(raiz->esq);
	preOrdem(raiz->dir);
}

// imprime os filhos da esquerda e da direita de uma árvore respectivamente.
void posOrdem(nodo_t* raiz){
	if (raiz == NULL) 
    return;
	preOrdem(raiz->esq);
	preOrdem(raiz->dir);
	printf("%i ",raiz->chave);
}

// retorna 1 se a arvore eh AVL e 0 caso contrario
int ehAVL(nodo_t* p){
	// alturas das arvores filhas do nodo p 
	int esq, dir;

	// se p nao for nulo 
	if(p != NULL){
		// verifica se as duas sub-arvores filhas de p sao AVL
		if(ehAVL(p->dir) && ehAVL(p->esq)){
			// descobre as alturas das duas sub-arvores filhas de p
			esq = alturaArvore(p->esq);
			dir = alturaArvore(p->dir);

			// caso a diferenca de altura entre as sub-arvores for maior que 1 ou menor que -1 retorna 0. 
			// Se nao, retorna 1
			if(esq-dir > 1 || esq-dir < -1) 
				return 0;  
			else 
				return 1;
		}
	}
	return 0;
}


// efetua a rotacao a direita
nodo_t* rotacaoDir(nodo_t* y){
	// o nodo x recebe o filho da esquerda de y
    nodo_t* x = y->esq;
	// o nodo z recebe o filho da direita de x (filho da direita do filho da esquerda de y)
    nodo_t* z = x->dir;

	// o filho da direita de x (filho da direita do filho da esquerda de y) recebe y
    x->dir = y;
	// o filho a esquerda de y recebe z (filho da direita do filho da esquerda do y original)
    y->esq = z;

	// efetua o rebalanceamento dos nodos rotacionados
    y->bal = max(alturaArvore(y->esq), alturaArvore(y->dir)) + 1;
    x->bal = max(alturaArvore(x->esq), alturaArvore(x->dir)) + 1;

	// retorna o novo nodo y
    return x;
}

nodo_t* rotacaoEsq(nodo_t* y){
	// o nodo y recebe o filho a direita de x
    nodo_t* x = y->dir;
	// o nodo z recebe o filho a esquerda de y (filho da esquerda do filho da direita de x)
    nodo_t* z = x->esq;

	// o filho da esquerda de x (filho da esquerda do filho da esquerda de y) recebe y
    x->esq = y;
	// o filho da direita de y recebe z (filho da esquerda do filho da direita de y)
    y->dir = z;

	// efetua o rebalanceamento dos nodos rotacionados
    y->bal = max(alturaArvore(y->esq), alturaArvore(y->dir)) + 1;
    x->bal = max(alturaArvore(x->esq), alturaArvore(x->dir)) + 1;

	// retorna o novo nodo y
    return x;
}


// retorna o valor do balanceamento do nodo p
int balanceamentoNodo(nodo_t *p){
    if (p == NULL)
        return 0;
    return alturaArvore(p->esq) - alturaArvore(p->dir);
}

nodo_t* inserirAVL(nodo_t* nodo, int chave){
	// caso o nodo nao exista, cria um novo nodo
    if (nodo == NULL)
        nodo = criaNodo(chave);
    
	// se a chave for menor que o nodo, chama a funcao novamente para o filho da 
	// esquerda do nodo. Caso a chave seja maior, chama a funcao para o filho da direita.
	// Se ja existir um nodo com a chave requerida, retorna o proprio nodo.
    if (chave < nodo->chave)
        nodo->esq  = inserirAVL(nodo->esq, chave);
    else if (chave > nodo->chave)
        nodo->dir = inserirAVL(nodo->dir, chave);
    else 
        return nodo;


	// incrementa em 1 o balanceamento do nodo que recebeu um novo filho
    nodo->bal = 1 + max(alturaArvore(nodo->esq), alturaArvore(nodo->dir));

	// pega o balanceamento do nodo
    int balanceamento = balanceamentoNodo(nodo);
 
	// se o balanceamento do nodo for maior que 1 e a chave do nodo da esqueda for 
	// maior do que a chave do nodo em questao efetua a rotacao a direita
    if (balanceamento > 1 && chave < nodo->esq->chave)
        return rotacaoDir(nodo);

 	// se o balanceamento do nodo for menor que -1 e a chave do nodo da direita for 
	// menor do que a chave do nodo em questao efetua a rotacao a esquerda
    if (balanceamento < -1 && chave > nodo->dir->chave)
        return rotacaoEsq(nodo);
 
  	// se o balanceamento do nodo for maior que 1 e a chave do nodo da esquerda for 
	// menor do que a chave do nodo em questao 
    if (balanceamento > 1 && chave > nodo->esq->chave){
		// efetua a rotacao a esquerda para o filho da esquerda do nodo em questao
        nodo->esq = rotacaoEsq(nodo->esq);
		// e retorna a rotacao a direita do nodo
        return rotacaoDir(nodo);
    }
  
  	// se o balanceamento do nodo for menor que -1 e a chave do nodo da direita for 
	// maior do que a chave do nodo em questao 
    if (balanceamento < -1 && chave < nodo->dir->chave){
		// efetua a rotacao a direita para o filho da direita do nodo em questao
        nodo->dir = rotacaoDir(nodo->dir);
		// e retorna a rotacao a esquerda do nodo
        return rotacaoEsq(nodo);
    }

    return nodo;
}

// retorna o menor valor da arvore de raiz p
nodo_t* min(nodo_t* nodo){
    nodo_t* aux = nodo;

    while (aux->esq != NULL)
        aux = aux->esq;
    return aux;
}
  
// deleta um nodo a partir da chave
nodo_t* deletarNodo(nodo_t* p, int chave) {

  // se a p fo nulo retorna a prorpia nodo
  if (p == NULL)
    return p;

  // esta proxima secao eh basicamente a busca binaria na arvore!
  // se a chave for menor do que a chave do nodo p 
  if (chave < p->chave)
	// chama a funcao novamente para o filho da esquerda de p ate que encontre o nodo a ser removido
    p->esq = deletarNodo(p->esq, chave);

  // se a chave for maior do que a chave do nodo p 
  else if (chave > p->chave)
	// chama a funcao novamente para o filho da direita de p ate que encontre o nodo a ser removido
    p->dir = deletarNodo(p->dir, chave);

  // se a chave for encontrada na arvore
  else {
	// se um dos filhos de p for nulo
    if ((p->esq == NULL) || (p->dir == NULL)) {
	  // caso o filho da esquerda exista, aux recebe o filho da esquerda. 
	  // Caso contrario, recebe o filho da direita
      nodo_t* aux = p->esq ? p->esq : p->dir;
	  
	  // se aux for nulo, aux recebe p, e p recebe NULL. Caso contrario, p recebe aux
      if (aux == NULL) {
        aux = p;
        p = NULL;
      } else
        p = aux;
	// se nenhum dos filhos de p forem nulos
    } else {
	  // o nodo aux recebe o valor minimo a partir da sub-arvore do filho da direita de p
      nodo_t* aux = min(p->dir);

	  // a chave de p passa a ser a chave de aux (valor minimo do filho da direita de p)
      p->chave = aux->chave;

	// chama a funcao novamente para o filho da direita de p ate que encontre o nodo a ser removido
      p->dir = deletarNodo(p->dir, aux->chave);
    }
  }

  // apos todas as manipulacoes na arvore, se p for nulo retorna p. 
  // Caso contrario, atualiza o valor da altura de p
  if (p == NULL)
    return p;
  p->bal = 1 + max(alturaArvore(p->esq), alturaArvore(p->dir));


  // pega o valor do balanceamento de p 
  int balanceamento = balanceamentoNodo(p);

  // se o balanceamento de p for maior que 1 e o balanceamento do filho a esquerda de 
  // p for maior ou igual a zero, efetua uma rotacao a direita
  if (balanceamento > 1 && balanceamentoNodo(p->esq) >= 0)
    return rotacaoDir(p);

  // se o balanceamento de p for maior que 1 e o balanceamento do filho a esquerda de 
  // p for menor que zero
  if (balanceamento > 1 && balanceamentoNodo(p->esq) < 0) {
	// efetua uma rotacao a esquerda para o filho a esquerda de p
    p->esq = rotacaoEsq(p->esq);
	// e uma rotacao a direita para p
    return rotacaoDir(p);
  }

  // se o balanceamento de p for menor que -1 e o balanceamento do filho a direita de 
  // p for menor ou igual a zero, efetua uma rotacao a esquerda
  if (balanceamento < -1 && balanceamentoNodo(p->dir) <= 0)
    return rotacaoEsq(p);

  // se o balanceamento de p for menor que -1 e o balanceamento do filho a direita de 
  // p for maior que zero
  if (balanceamento < -1 && balanceamentoNodo(p->dir) > 0) {
	// efetua uma rotacao a direita para o filho a direita de p
    p->dir = rotacaoDir(p->dir);
	// e uma rotacao a esquerda para p
    return rotacaoEsq(p);
  }

  return p;
}

// gera a saida no arquivo .out do teste
void imprimeSaida(nodo_t* raiz, nodo_t* p, FILE* out){
	// se p (raiz) for nulo para a funcao
	if (p == NULL) 
		return;
	// efetua a passagem em ordem de cada elemento da arvore, 
	// e imprime a chave do elemento e seu nivel na arvore
	imprimeSaida(raiz, p->esq, out);
	fprintf(out, "%d,%d\n", p->chave, p->bal);
	imprimeSaida(raiz, p->dir, out);
}

int main(int argc, char *argv[]){
  // inicializa o nodo da raiz em NULL
  nodo_t* raiz = NULL;

  // inicializa os arquivos que serao utilizados (teste.in e teste.out)
  FILE *ent, *out;

  // le os argumentos da inicializacao do programa
  char* entrada = argv[1], *saida = argv[2];

  // inicializa strings para manejar os inputs do usuario
  char input[15], *aux;
  char ch;
  int num;

  // abre o arquivo de entrada e cria o arquivo de saida
  ent = fopen(entrada, "r");
  out = fopen(saida, "w");

  // caso algum dos arquivos nao tenha aberto corretamente, finaliza a execucao do codigo
  if (!ent || !out) 
      return 0;

  // le a primeira linha do arquivo de entrada
  fgets(input, 15, ent);

  // enquanto o arquivo nao tiver acabado
  while (!feof(ent)){
      // coloca o input char na variavel ch e o numero em questao na variavel num
      ch = input[0];
      aux = strchr(input, ' ');
      // transforma o numero de string para int
      num = atoi(aux);


      // analisa os casos de remocao ou insercao
      if (ch == 'i'){
        raiz = inserirAVL(raiz, num);
      } else if (ch == 'r'){
        raiz = deletarNodo(raiz, num);
      }
      
      // le a proxima linha do arquivo de entrada
      fgets(input, 15, ent);
  }

  // cria um nodo auxiliar para ser modificado na funcao imprime saida
  nodo_t* nodoAux = raiz;
  imprimeSaida(raiz, nodoAux, out);

  // fecha os arquivos utilizados e termina a execucao do programa
  fclose(ent);
  fclose(out);
  
  return 0;
}