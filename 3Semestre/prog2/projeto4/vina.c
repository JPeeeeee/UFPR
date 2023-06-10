#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include <sys/stat.h>

struct header {
    char **info;
    int size;
};

struct file_info {
    char *name;
    char *path;
    int UID;
    int permission;
    int order;
    int size;
};

void get_dados_arquivo(FILE *arquivo) {
    printf("salve salve fml\n");
};

int main (int argc, char *argv[]) {

    	// get_dados_arquivo(argv[1]);

	int option;

	while (option = getopt(argc, argv, "i:a:x:m:r:ch") != -1) {
		switch (option) {
			case 'h':
				printf("
    -i : insere/acrescenta um ou mais membros ao archive. Caso o membro ja exista no archive, ele deve ser substituido. Novos membros sao inseridos respeitando a ordem da linha de comando, ao final do archive;\n
    -a : mesmo comportamento da opcao -i, mas a substituicao de um membro existente ocorre APENAS caso o parametro seja mais recente que o arquivado;\n
    -m target : move o membro indicado na linha de comando para imediatamente depois do membro target existente em archive. A movimentação deve ocorrer na secao de dados do archive;\n
    -x : extrai os membros indicados de archive. Se os membros nao forem indicados, todos devem ser extraidos. A extracao consiste em ler o membro de archive e criar um arquivo correspondente, com conteudo identico, em disco;\n
    -r : remove os membros indicados de archive;\n
    -c : lista o conteudo de archive em ordem, incluindo as propriedades de cada membro (nome, UID, permissoes, tamanho e data de modificacao) e sua ordem no arquivo. A saida esperada eh igual ao do comando tar com as opcoes tvf\n
    -h : imprime uma pequena mensagem de ajuda com as opcoes disponiveis e encerra.\n
				");
				break;
			default:
				break;
		}
	}

  return 0;
}
	
