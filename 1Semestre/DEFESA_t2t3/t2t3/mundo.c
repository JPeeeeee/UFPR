#include <stdio.h>
#include <stdlib.h>
#include "libconjunto.h"
#include "libfila.h"
#include "liblef.h"


struct pessoa {
    int id;
    int extroversao;
    int paciencia;
    int idade;
    conjunto_t *CRC;
};
typedef struct pessoa pessoa_t;

struct local {
    int id;
    int lotacao;
    conjunto_t *publico;
    fila_t *fila;
    int localizacao[2];
};
typedef struct local local_t;

struct mundo {
    int tempo_atual;
    conjunto_t *rumores;
    int Npessoas;
    int Nlocais;
    int NtamanhoMundo;
    pessoa_t *pessoas;
    local_t *locais;
};
typedef struct mundo mundo_t;

/* eventos */
struct chegada {
    int idLocal;
    int idPessoa;
};
typedef struct chegada chegada_t;

struct saida {
    int idLocal;
    int idPessoa;
};
typedef struct saida saida_t;

struct disseminacao {
    int idLocal;
    int idPessoa;
    conjunto_t *pessoasNoLocal;
    conjunto_t *rumoresDaPessoa;
};
typedef struct disseminacao disseminacao_t;

struct fim {
    int fim_dos_tempos;
};
typedef struct fim fim_t;

void destroidados(void *chegada){
    free(chegada);
}

void evento_chegada(lef_t *l, chegada_t *chegada_dados, int tempo_fim){
    evento_t *chegada = malloc(sizeof(evento_t));
    chegada->tempo = rand() % tempo_fim;
    chegada->tipo = 1;
    chegada->tamanho = sizeof(chegada_t);
    chegada->dados = malloc(sizeof(chegada_t));
    chegada->dados = chegada_dados;
    chegada->destroidados = &destroidados;
    adiciona_ordem_lef(l, chegada);
}

void evento_saida(lef_t *l, saida_t *saida_dados, int tempo_atual, int tempo_saida){
    evento_t *saida = malloc(sizeof(evento_t));
    saida->tempo = tempo_atual + tempo_saida;
    saida->tipo = 2;
    saida->tamanho = sizeof(saida_t);
    saida->dados = saida_dados;
    saida->destroidados = &destroidados;
    adiciona_ordem_lef(l, saida);
}

void evento_disseminacao(lef_t *l, disseminacao_t *disseminacao_dados, int tempo_atual, int tempo_fim){
    evento_t *disseminacao = malloc(sizeof(evento_t));
    disseminacao->tempo = tempo_atual + rand() % tempo_fim;
    disseminacao->tipo = 3;
    disseminacao->tamanho = sizeof(disseminacao_t);
    disseminacao->dados = disseminacao_dados;
    disseminacao->destroidados = &destroidados;
    adiciona_ordem_lef(l, disseminacao);
}

void evento_fim(lef_t *l, fim_t *fim_dados){
    evento_t *fim = malloc(sizeof(evento_t));
    fim->tempo = fim_dados->fim_dos_tempos;
    fim->tipo = 4;
    fim->tamanho = sizeof(fim_t);
    fim->dados = fim_dados;
    fim->destroidados = &destroidados;
    adiciona_ordem_lef(l, fim);
}

/* entidades */
pessoa_t cria_pessoa(mundo_t *mundo){
    pessoa_t pessoa;

    pessoa.id = mundo->Npessoas;
    pessoa.extroversao = rand() % 100;
    pessoa.paciencia = rand() % 100;
    pessoa.idade = 18 + rand() % (92);
    pessoa.CRC = cria_conjunto(1 + rand() % (4));

    int i;
    for (i = 0; i < pessoa.CRC->max; i++)
        insere_conjunto(pessoa.CRC, rand() % 30); 

    return pessoa;
}

void destroi_pessoa(mundo_t *mundo, int id){
    destroi_conjunto(mundo->pessoas[id].CRC);
    int i;
    for (i = id; i < mundo->Npessoas; i++)
        mundo->pessoas[i] = mundo->pessoas[i+1];
}

local_t cria_local(mundo_t *mundo){
    local_t local;

    local.id = mundo->Nlocais;
    local.lotacao = 5 + rand() % (10);
    local.publico = cria_conjunto(local.lotacao);
    local.fila = cria_fila();
    local.localizacao[0] = rand() % mundo->NtamanhoMundo - 1;
    local.localizacao[1] = rand() % mundo->NtamanhoMundo - 1;

    return local;
}

void destroi_local(mundo_t *mundo, int id){
    destroi_fila(mundo->locais[id].fila);
    int i;
    for (i = id; i < mundo->Nlocais - 1; i++)
        mundo->locais[i] = mundo->locais[i+1];
}

mundo_t *cria_mundo(){
    mundo_t *mundo = malloc(sizeof(mundo_t));    
    if (mundo == NULL)
        return NULL;
    
    mundo->tempo_atual = 0;
    mundo->Npessoas = 0;
    mundo->Nlocais = 0;
    mundo->rumores = cria_conjunto(30);    
    mundo->pessoas = malloc(sizeof(pessoa_t) * 100);
    mundo->locais = malloc(sizeof(local_t) * 8);
    mundo->NtamanhoMundo = 20000;
    
    return mundo;
}

void destroi_mundo(mundo_t *mundo){
    destroi_conjunto(mundo->rumores);
    free(mundo);
}

int main(){
    srand(21);
    int tempo_fim = 1000;
    int tempo_atual = 0;
    mundo_t *mundo = cria_mundo();
    lef_t *lef = cria_lef();


    int i;
    /* cria os locais do mundo */
    for(i = 0; i < 8; i++){
        mundo->locais[i] = cria_local(mundo);
        mundo->Nlocais += 1;
    }

    /* cria as pessoas do mundo */
    for (i = 0; i < 100; i++){
        mundo->pessoas[i] = cria_pessoa(mundo);
        mundo->Npessoas += 1;
    }

    /* cria eventos de chegada para 100 pessoas */
    for (i = 0; i < 100; i++){
        chegada_t *chegada_dados = malloc(sizeof(chegada_t));
        chegada_dados->idLocal = rand() % mundo->Nlocais;
        chegada_dados->idPessoa = i;

        evento_chegada(lef, chegada_dados, tempo_fim);
    }


    fim_t *fim_dados = malloc(sizeof(fim_t));
    fim_dados->fim_dos_tempos = tempo_fim;
    evento_fim(lef, fim_dados);

    int publico, lotacao;

    while(lef->Primeiro->evento->tipo != 4){
        evento_t *primeiro_evento = obtem_primeiro_lef(lef);
        tempo_atual = primeiro_evento->tempo;

        switch(primeiro_evento->tipo){
            case 1:
                {
                    /* Lida com o evento de chegada de uma pessoa em um local
                     * Se o local ja estiver lotado (publico == lotacao)
                     * insere a pessoa na fila do local
                    */
                    chegada_t *chegada;
                    chegada = primeiro_evento->dados;
                    publico = mundo->locais[chegada->idLocal].publico->card;
                    lotacao = mundo->locais[chegada->idLocal].lotacao;
                    if(publico == lotacao){
                        insere_fila(mundo->locais[chegada->idLocal].fila, chegada->idPessoa);
                        printf("%6d:CHEGA Pessoa%4d Local%2d (%2d/%2d), FILA %d\n", tempo_atual, chegada->idPessoa, chegada->idLocal, publico, lotacao, tamanho_fila(mundo->locais[chegada->idLocal].fila));
                        break;
                    }


                    /* Cria o evento de saida do local
                     * Considera a paciencia da pessoa 
                     * para decidir qual sera o tempo de saida.
                    */
                    saida_t *saida_dados = malloc(sizeof(saida_t));
                    saida_dados->idLocal = chegada->idLocal;
                    saida_dados->idPessoa = chegada->idPessoa;
                    evento_saida(lef, saida_dados, tempo_atual, ((mundo->pessoas[chegada->idPessoa].paciencia)/10+(rand()%tempo_atual)));


                    /* Imprime a mensagem de chegada */
                    insere_conjunto(mundo->locais[chegada->idLocal].publico, chegada->idPessoa);
                    printf("%6d:CHEGA Pessoa%4d Local%2d (%2d/%2d), ENTRA\n", tempo_atual, chegada->idPessoa, chegada->idLocal, publico, lotacao);



                    /* Cria evento de rumor para o local que 
                     * acabou de receber o evento de chegada
                     * e adiciona o evento na LEF.
                    */
                    disseminacao_t *disseminacao_dados = malloc(sizeof(disseminacao_t));
                    disseminacao_dados->pessoasNoLocal = mundo->locais[chegada->idLocal].publico;     
                    disseminacao_dados->rumoresDaPessoa = mundo->pessoas[chegada->idPessoa].CRC; 
                    disseminacao_dados->idLocal = chegada->idLocal;
                    disseminacao_dados->idPessoa = chegada->idPessoa;
                    evento_disseminacao(lef, disseminacao_dados, tempo_atual, tempo_fim);   

                    break;
                }
            case 2:
                {
                    /* Lida com o evento de saida.
                     * Caso o publico do local seja 0, ou seja, 
                     * o local esteja vazio, libera o 
                     * evento de saida alocado. 
                    */
                    saida_t *saida;
                    saida = primeiro_evento->dados;
                    publico = mundo->locais[saida->idLocal].publico->card;
                    lotacao = mundo->locais[saida->idLocal].lotacao;

                    if(publico == 0){
                        free(saida);
                        break;
                    }


                    /* Se a fila do local nao estiver vazia,
                     * retira a pessoa em questao do local e 
                     * insere a primeira pessoa da fila e termina o evento.
                    */
                    if(!fila_vazia(mundo->locais[saida->idLocal].fila)){
                        int idSaiuDaFila = mundo->locais[saida->idLocal].fila->ini->chave;
                        retira_fila(mundo->locais[saida->idLocal].fila, &idSaiuDaFila);
                        retira_conjunto(mundo->locais[saida->idLocal].publico, saida->idPessoa);
                        printf("%6d:SAIDA Pessoa%4d Local%2d (%2d/%2d), REMOVE FILA Pessoa%6d\n", tempo_atual, saida->idPessoa, saida->idLocal, publico, lotacao, idSaiuDaFila);
                        printf("%6d:CHEGA Pessoa%4d Local%2d (%2d/%2d), ENTRA\n", tempo_atual, idSaiuDaFila, saida->idLocal, publico, lotacao);
                        break;
                    }



                    /* Caso seja um evento de saida comum,
                     * retira a pessoa do conjunto "publico"
                     * do local em questao e imprime a mensagem
                     * de saida.
                    */
                    retira_conjunto(mundo->locais[saida->idLocal].publico, saida->idPessoa);
                    printf("%6d:SAIDA Pessoa%4d Local%2d (%2d/%2d)\n", tempo_atual, saida->idPessoa, saida->idLocal, publico, lotacao);

                    break;
                }
            case 3:
                {
                    /* Lida com o evento de disseminacao.
                     * Caso nao existam pessoas no local
                     * de disseminacao, termina o evento.
                    */
                    disseminacao_t *disseminacao;
                    disseminacao = primeiro_evento->dados;

                    if (disseminacao->pessoasNoLocal->card == 0){
                        free(disseminacao);
                        break;
                    }

                    /* Caso o resultado do rand seja 0, 
                     * escolhe outro numero aleatorio
                    */
                    int Npessoas = disseminacao->pessoasNoLocal->card;
                    while (Npessoas == 0)
                        Npessoas = rand() % disseminacao->pessoasNoLocal->card;


                    /* Cria o subconjunto de pessoas que ouviram 
                     * e imprime as pessoas que acreditaram no rumor
                     * considerando a extroversao de cada uma.
                    */    
                    conjunto_t *pessoasQueOuviram = cria_subconjunto(disseminacao->pessoasNoLocal, rand() % Npessoas);
                    int rumor;
                    int j;
                    printf("%6d:RUMOR Pessoa%4d Local%2d ", tempo_atual, disseminacao->idPessoa, disseminacao->idLocal);
                    for (j = 0; j < pessoasQueOuviram->card; j++){
                        rumor = disseminacao->rumoresDaPessoa->v[rand() % disseminacao->rumoresDaPessoa->card];
                        if(rand() % 100 < mundo->pessoas[pessoasQueOuviram->v[j]].extroversao){

                            /* Retira rumor do conjunto primeiro para 
                             * garantir que nao se repitam rumores no
                             * CRC da pessoa que vai receber o rumor.
                            */
                            retira_conjunto(mundo->pessoas[pessoasQueOuviram->v[j]].CRC, rumor);
                            insere_conjunto(mundo->pessoas[pessoasQueOuviram->v[j]].CRC, rumor);
                            printf("(P%d:R%d)  ", mundo->pessoas[pessoasQueOuviram->v[j]].id, rumor);
                        }
                    }
                    printf("\n");
                    break;
                }
            case 4:
                return 0;
            default:
                break;
        }
    }

    destroi_lef(lef);

    return 0;
}
