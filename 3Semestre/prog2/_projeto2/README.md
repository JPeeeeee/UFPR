
# Cifra de Beale

Programa que codifica e decodifica mensagens utilizando a Cifra de Beale

Trabalho para a disciplina de Programação 2


## Funcionalidades

- Encode
- Decode com um arquivo de chaves
- Decode com um livro cifra


## Descrição das bibliotecas

## LibArquivoChaves

Esta biblioteca foi criada com o intuito de modularizar a criação do arquivo de chaves.

Ela possui duas funções principais:

- **cria_lista_encode**, que retorna a estrutura lista contendo todas as primeiras letras de cada palavra presente do livro cifra e chaves que indicam a posição de cada uma das palavras no livro
```C
fila_t *cria_lista_encode(FILE *LivroCifra){
	fila_t *f = cria_fila();

	if (LivroCifra == NULL)
		return NULL;

	char palavra[BUFF];
	int p = 0;

	// le cada uma das letras do livro cifra 
    // e insere a primeira letra na estrutura fila
	while (fscanf(LivroCifra, "%s", palavra) != EOF) { 

		char primeira_letra;

		primeira_letra = palavra[0];

		// Para caso de um arquivo convertido para UTF-8, por exemplo, 
        // desconsidera os primeiros caracteres que avisam da conversão
		// if (p == 0){
		// 	primeira_letra = palavra[3];
		// }

		primeira_letra = tolower(primeira_letra);

		// so insere a letra na fila se ela existir nos 127 valores da tabela ASCII
		if (primeira_letra <= 127)
			insere_fila(f, primeira_letra, p);

		p++;
				
	}

	return f;
}
```
- **gera_arquivo_chaves**, que cria o arquivo de chaves a partir da estrutura gerada na ultima função, no diretório atual do usuário
```C
void gera_arquivo_chaves(FILE *ArquivoChaves, fila_t *f) {
	nodo_f_t *aux = f->ini;

	// itera por toda a lista e printa a letra e chaves de cada nodo
    for (int i = 0; i < tamanho_fila(f); i++){
        fprintf(ArquivoChaves, "%c:", aux->letra);

        for (int j = 0; j < aux->tamanho; j++) {
            fprintf(ArquivoChaves, " %d", aux->chaves[j]);
        }

        fprintf(ArquivoChaves, "\n");
        aux = aux->prox;
    }
}
```
---
## LibFila

### A struct fila e struct nodo

A lista que foi utilizada no projeto utiliza a política **FIFO**, por isso o nome fila. A struct ficou da seguinte maneira:

```C
struct fila {
    nodo_f_t *ini;        
    nodo_f_t *fim;       
    int tamanho;     
};
```
Um ponteiro que representa o início da fila, outro para o fim e um inteiro que guarda o numero de nodos presentes na fila.

E a struct nodo:

```C
struct nodo_f {
    char letra;
    struct nodo_f *prox; 
    int *chaves;
    int tamanho;
};
```
Cada nodo recebe um char letra, um ponteiro pra o próximo elemento, um vetor de chaves que contem a posição de todas as palavras do livro cifra que começam com char letra, e um inteiro que representa o número de chaves presentes no vetor de inteiros.
 
---
### Funções

Para facilitar a criação da estrutura principal para o arquivo de chaves, a LibFila possui as seguintes funções:

- **cria_fila**, retorna um ponteiro para uma estrutura fila recém criada
```C
fila_t * cria_fila ();
```
- **destroi_fila**, destroi a fila e libera toda a memoria utilizada pela estrutura
```C
void destroi_fila (fila_t *f);
```
- **fila_vazia**, verifica se a fila esta vazia, retorna 1 caso esteja e 0 caso contrario
```C
int fila_vazia(fila_t *f);
```
- **tamanho_fila**, retorna um inteiro que representa o tamanho da fila
```C
int tamanho_fila (fila_t *f);
```
- **insere_fila**, verifica a existencia do char c na fila. Caso ja exista insere a chave no nodo de letra c, caso contrario cria um novo nodo com a letra c e insere a chave. Retorna 1 se a insercao foi bem sucedida e 0 em caso de falha
```C
int insere_fila (fila_t *f, char c, int chave);
```
Vale ressaltar que nessa função aloca dinamicamente o vetor de chaves para o nodo, da seguinte forma:

Obs: A funcao **adiciona_chave** será explicada logo depois do exemplo de código

```C
int insere_fila (fila_t* f, char c, int chave) {

    // caso o valor ja exista na fila, chama a funcao adiciona_chave
    if (busca_fila(f, c)){
        adiciona_chave(f, c, chave);
        return 1;
    }

    nodo_f_t *novo = malloc(sizeof(nodo_f_t));
    
    if (novo == NULL)
        return 0;
    
    // inicializa os valores do novo nodo e aloca o tamanho de um unico 
    // valor int e insere a chave na primeira posicao do vetor
    novo->letra = c;
    novo->prox = NULL;
    novo->chaves = malloc(sizeof(int));
    novo->chaves[0] = chave;
    novo->tamanho = 1;

    // reajusta os ponteiros de inicio e fim da fila
    if (fila_vazia(f)){
        f->ini = novo;
        f->fim = novo;
        f->tamanho++;
        return 1;
    } else{
        nodo_f_t *aux = f->fim;
        f->fim = novo;
        aux->prox = f->fim;
        f->tamanho++;
        return 1;
    }
}
```
A funcao **adiciona_chave** só é chamada caso seja preciso adicionar uma chave na fila e a letra que ela representa já esteja entre os nodos da estrutura.

```C
int adiciona_chave (fila_t *f, char c, int chave) {

    // aux recebe o nodo com letra 'char c'
    nodo_f_t *aux = busca_fila(f, c);

    if (aux == NULL)
        return 0;

    // o vetor de chaves de aux recebe um realloc de tamanho 
    aux->tamanho++;
    aux->chaves = realloc(aux->chaves, sizeof(int) * aux->tamanho);
    aux->chaves[aux->tamanho - 1] = chave;
    return 1;

}
```
- **busca_fila**, busca um nodo de letra c na estrutura fila e retorna um ponteiro para ele
```C
nodo_f_t *busca_fila (fila_t *f, char c);
```
---
## LibCodifica

A LibCodifica, feita para garantir que as mensagens sejam codificadas da maneria certa, carrega as seguintes funções:

- **coleta_dados_texto_fila**, que é responsável por chamar as funções necessárias para a codificação da mensagem, além de alocar e desalocar as estruturas que serão utilizadas durante o processo
```C
void coleta_dados_texto_fila (FILE *LivroCifra, FILE *ArquivoChaves, FILE *MensagemSaida, FILE *MensagemEntrada);
```
- **codifica_mensagem** é uma função privada da biblioteca de codificação que é responsável por ler a mensagem de entrada e inserir
```C
void codifica_mensagem(fila_t *f, FILE *MensagemEntrada, FILE *MensagemSaida);
```
Esta função encontra nodos com cada uma das letras presentes na mensagem de entrada, e escolhe um dos numeros no vetor de chaves do nodo para ser utilizado como representante da letra na mensagem final. Além disso, imprime -1 para **espaços** e -2 para **quebra de linhas**.

---

## LibDecodifica

Para a biblioteca de decodificação, temos 4 funções:

A duas principais são: 
- **decodifica_mensagem_chaves**, que decodifica as mensagens usando o arquivo de chaves

```C
void decodifica_mensagem_chaves (FILE *ArquivoChaves, FILE *MensagemSaida, FILE *MensagemEntrada);
```

- **decodifica_mensagem_livro**, que decodifica as mensagens usando o livro cifra
```C
void decodifica_mensagem_livro (FILE *LivroCifra, FILE *MensagemSaida, FILE *MensagemEntrada);
```

A maior diferença entre as duas funções é o modo como as letras são encontradas a partir da mensagem codificada.

Para decodificar a mensagem com o arquivo de chaves, utilizamos **encontra_letra_arquivo_chaves**:
```C
char encontra_letra_arquivo_chaves(FILE *ArquivoChaves, int chave_letra_requerida) { 

    // garante que a leitura do arquivo comecara do lugar certo
    rewind(ArquivoChaves);

    char letra, espaco;
    int numero;

    // enquanto nao for o fim do arquivo...
    // guarda a letra atual na variavel letra
    while (fscanf(ArquivoChaves, "%c:", &letra) != EOF) {

        // le os espacos entre as chaves e guarda na variavel espaco
		espaco = fgetc(ArquivoChaves);
        fscanf(ArquivoChaves, "%d", &numero);

        // enquanto as chaves lidas ainda forem da mesma letra, 
        // compara a chave com o inteiro passado para a funcao
        while (espaco != '\n') {
            espaco = fgetc(ArquivoChaves);
            if (chave_letra_requerida == numero){
                return letra;
            }
            fscanf(ArquivoChaves, "%d", &numero);
        }
	}
    return ' ';
}
```

A função lê o arquivo de chaves procurando a chave recebida da mensagem codificada e retorna a letra que a chave representa.

---
\
Já para decodificar com o livro cifra, utilizamos **encontra_letra_livro**:

```C
char encontra_letra_lista (fila_t *f, int chave_letra_requerida) {

    char letra;

    nodo_f_t *aux = f->ini;

    // itera por cada um dos nodos da fila
    for (int i = 0; i < tamanho_fila(f); i++){
        letra = aux->letra;
        
        // compara cada um dos elementos do vetor com a chave e, em caso positivo
        // retorna a letra do nodo
        for (int j = 0; j < aux->tamanho; j++) {
            if (chave_letra_requerida == aux->chaves[j])
                return letra;
        }
        aux = aux->prox;
    }

    return ' ';
}
```
Como neste case recebemos apenas o livro cifra, é necessário criar a estrutura fila para poder encontrar a letra. A função verifica a existencia da chave da letra requerida no vetor de chaves de cada nodo.

---

## Beale

Beale é a a funçõa main do programa. É aqui que os parâmetros são tratados utilizando a função optarg.

### Lidando com as opções do programa

- **-e (Encode)**

```
./beale -b LivroCifra.txt -m MensagemEntrada.txt -o MensagemCodificada.txt -c ArquivoChaves.txt
```

Opção para codificar uma mensagem utilizando um livro cifra. 

O programa irá codificar a mensagem e criar um arquivo de chaves no diretório atual do usuário. 

Obs: O encode só será realizado se **todos** os parâmetros necessários para a operação estiverem no comando.

```C
if (flag_e){

    // abre arquivo de chaves em modo write
    arquivo_chaves = fopen(nomeArquivoChaves, "w");

    if (livro_cifra == NULL || arquivo_chaves == NULL || mensagem_saida == NULL || mensagem_entrada == NULL){
        close_files(livro_cifra, mensagem_entrada, mensagem_saida, arquivo_chaves);
        return printf("Erro ao abrir um ou mais aquivos! Tente novamente!\n");
    }

    coleta_dados_texto_fila(livro_cifra, arquivo_chaves, mensagem_saida, mensagem_entrada);
}
```

- **-d (Decode)**

A opção decode pode ter dois comportamentos diferentes, visto que uma mensagem pode ser decodificada por meio de um livro cifra ou um arquivo de chaves.

No caso do uso de um arquivo de chaves, temos o seguinte comando: 

```C
./beale -b LivroCifra.txt -i MensagemCodificada.txt -o MensagemDecodificada.txt
```
E no caso do livro de cifras:
```C
./beale -c ArquivoDeChaves.txt -i MensagemCodificada.txt -o MensagemDecodificada.txt
```
Neste caso, precisamos garantir que somente as opções necessárias e possíveis estejam sendo chamadas, então temos:

```C
if (flag_d && flag_c && !flag_b) { // opcao decode com arquivo de chaves

    // abre arquivo de chaves em modo read
    arquivo_chaves = fopen(nomeArquivoChaves, "r");

    if (arquivo_chaves == NULL || mensagem_saida == NULL || mensagem_entrada == NULL){
        close_files(livro_cifra, mensagem_entrada, mensagem_saida, arquivo_chaves);
        return printf("Erro ao abrir um ou mais aquivos! Tente novamente!\n");
    }
    
    decodifica_mensagem_chaves(arquivo_chaves, mensagem_saida, mensagem_entrada);

} else if (flag_d && flag_b && !flag_c) { // opcao decode com livro de chaves       

    if (livro_cifra == NULL || mensagem_saida == NULL || mensagem_entrada == NULL){
        close_files(livro_cifra, mensagem_entrada, mensagem_saida, arquivo_chaves);
        return printf("Erro ao abrir um ou mais aquivos! Tente novamente!\n");
    }

     decodifica_mensagem_livro(livro_cifra, mensagem_saida, mensagem_entrada);
}
```

Por fim, caso alguma das opções tenha sido usada de maneira indevida:

```C
else { // erro nos argumentos na chamada do programa

    close_files(livro_cifra, mensagem_entrada, mensagem_saida, arquivo_chaves);

    printf("Erro ao abrir um ou mais aquivos! Tente novamente!\n");
    return -1;
} 
```

Obs: A função **close_files** fecha os arquivos abertos durante a manipulação dos parâmetros. Ela recebe todas as variáveis tipo FILE que podem receber um arquivo, verifica os que são diferentes de NULL e os fecha.

```C
void close_files(FILE *livro_cifra, FILE *mensagem_entrada, FILE *mensagem_saida, FILE *arquivo_chaves) {
    if (livro_cifra)
        fclose(livro_cifra);
    if (mensagem_entrada)
        fclose(mensagem_entrada);
    if (arquivo_chaves)
        fclose(arquivo_chaves);
    if (mensagem_saida)
        fclose(mensagem_saida);
}
```

---