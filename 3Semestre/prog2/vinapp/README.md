
# Vina++

Programa que cria um arquivo de backup (sem compressão)

Trabalho para a disciplina de Programação 2


## Funcionalidades

- Inserir arquivos no arquivo de backup
- Excluir arquivos no arquivo de backup
- Extrair arquivos para o diretorio atual
- Mostrar arquivos presentes no backup
- Modificar a ordem dos arquivos dentro do backup


## Descrição das bibliotecas

## LibManageFiles

Esta biblioteca foi criada com o intuito de modularizar as operações com arquivos.

Ela possui cinco funções principais:

- **transcreveArquivo**, que escreve o arquivo sendo adicionado no arquivo backup utilizando leitura bufferizada.

- **inclusaoDeArquivo**, que organiza as ações necessárias para inserir o arquivo no backup

- **removeArquivo**, que exclui o arquivo especificado do arquivo de backup

- **extraiArquivo**, que extrai os arquivos especificados para o diretorio atual

- **moveArquivo**, que move o arquivo desejado para a posição logo abaixo do arquivo especificado na chamada do programa
---
## LibFila

### A struct fila e struct nodo

A estrutura da fila:

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
    char *nome;
    char *path;
    uid_t UID;
    gid_t group;
    time_t dataAlteracao;
    int posicao;
    off_t tam;
    int b_ini;
    int b_fim;
    mode_t permissoes;
    struct nodo_f *prox;
};
```
Cada nodo recebe um nome, caminho, ID, grupo, data da última alteração, posição no arquivo backup, tamanho, bit de início, bit de fim, permissões e um ponteiro para o próximo nodo. Todas essas informações servem para garantir que a manipulação dos arquivos inseridos será feita da melhor maneira.
 
---
### Funções

Para facilitar a criação da estrutura principal para o arquivo de chaves, a LibFila possui as seguintes funções:

- **cria_fila**, retorna um ponteiro para uma estrutura fila recém criada
```C
fila_t * cria_fila ();
```

- **fila_vazia**, verifica se a fila esta vazia, retorna 1 caso esteja e 0 caso contrario
```C
int fila_vazia(fila_t *f);
```
- **tamanho_fila**, retorna um inteiro que representa o tamanho da fila
```C
int tamanho_fila (fila_t *f);
```
- **insere_fila**, verifica a existencia do arquivo na fila. Caso ja exista não faz nada e retorna, caso contrario cria um novo nodo com as informações do arquivo e insere na fila. Retorna 1 se a insercao foi bem sucedida e 0 em caso de falha
```C
int insere_fila (fila_t *f, char *name, FILE *arqBackup);
```

- **insere_nodo_fila**, retorna 1 se a insercao foi bem sucedida e 0 em caso de falha. Diferente da funcao anterior, esta recebe um nodo pronto como parametro

```C
int insere_nodo_fila(fila_t *f, nodo_f_t *novo);
```

- **remove_fila**, remove um nodo da estrutura fila. Essa função recebe o nodo a ser excluido como parâmetro
```C
void remove_fila (fila_t *f, nodo_f_t *removido);
```

- **busca_fila**, busca um nodo de nome *char name* na estrutura fila e retorna um ponteiro para ele
```C
nodo_f_t *busca_fila (fila_t *f, char *name);
```
---
## LibUtils

A LibUtils, feita para auxiliar em alguns processos longos e repetitivos durante o código, carrega as seguintes funções:

- **imprimeDiretorio**, que é responsável imprimir as informações presentes nos nodos da estrutura diretorio

- **lacoEscrita** é a função que escreve as informações da estrutura diretorio no 

- **escreveDiretorio** organiza os bits de inicio do diretorio, tamanho da estrutura e escreve o diretorio no arquivo backup. Essa função funciona juntamente da anterior.

- **leDiretorio**, le o diretorio presente no arquivo backup e carrega as informacoes para uma estrutura de dados em memoria

- **tamanhoArquivo**, como o nome sugere, retorna o tamanho de um arquivo ja aberto :)

- **removeBytes**, remove os bytes entre 'comeco' e 'fim' (bits do arquivo backup) e escreve o que estava logo abaixo deles para cima.

---

## Vina++

Vina++ é a a funçõa main do programa. É aqui que os parâmetros são tratados utilizando a função optarg.

### Lidando com as opções do programa

- **-i (Inserir arquivo)**

```
./vina++ -i backup.vpp arquivo1.txt arquivo2.txt
```

Opção para inserir um arquivo. 

Obs. Lembre-se de colocar o arquivo de backup como o primeiro parâmetro ao rodar os comandos!

- **-r (Remove arquivo)**

A opção que remove um arquivo do backup. Caso o arquivo não exista lá dentro, uma lista com os já existentes é mostrada.

```C
./vina++ -r backup.vpp arquivo2.txt
```

- **-a (Atualiza arquivo)**

Caso tenha feito alguma alteração em um arquivo que já está dentro do backup e queria modificá-lo lá dentro, essa é a melhor opção.

```C
./vina++ -a backup.vpp arquivo2.txt
```

Se o arquivo não existir no backup ele é criado automaticamente, e se não forem necessárias atualizações o programa não faz nada

- **-m (Mover arquivo)**

Opção que manda um arquivo ja existente dentro do backup para um espaço logo abaixo do arquivo especificado na chamada do programa.

```C
./vina++ -m backup.vpp arquivo1.txt arquivo2.txt
```

Obs. Neste caso o "arquivo1.txt" será enviado para depois do "arquivo2.txt"

- **-c (Imprime arquivos do backup)**

Para caso queira ter uma visão mais ampla dos arquivos presentes no backup. (Semelhante ao tar -tvf)

```C
./vina++ -c backup.vpp 
```

Obs. Esta opção recebe **somente** o arquivo backup como parâmetro!

- **-x (Extrair arquivos)**

Opção para extrair os arquivos do backup para o diretório atual

```C
./vina++ -x backup.vpp arquivo1.txt arquivo2.txt
```

- **-h (HELP!)**

Imprime todos os possíveis comandos relacionados ao vina++ no terminal

```C
./vina++ -h
```

---