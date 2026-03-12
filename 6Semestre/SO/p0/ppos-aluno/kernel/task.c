// PingPongOS - PingPong Operating System

// Task Control Block (TCB), infos sobre uma tarefa
// struct task_t
// {
//     int id;                     // identificador da tarefa
//     char *name;                 // nome da tarefa
//     struct ctx_t context;       // contexto armazenado da tarefa
//                                 // ...
// };

#include "tcb.h"
#include "ctx.h"
#include <stdio.h>
#include <stdlib.h>

void task_init()
{

}

// cria uma nova tarefa: "name" é o nome da tarefa, "entry"
// é a função que ela irá executar e "arg" aponta para o valor
// recebido por "entry" ao iniciar (pode ser NULL).
// retorno: ptr para o descritor da tarefa ou NULL se houver erro
struct task_t *task_create(char *name, void (*entry)(void *), void *arg) {
    struct task_t *newTask = malloc(sizeof(struct task_t));
    void *stack = malloc(sizeof(16));

    newTask->name = name;
    // newTask->id = 

    ctx_create(&newTask->context, entry,
               arg, stack, 16);
}

// destroi uma tarefa e libera seus recursos;
// somente deve atuar sobre tarefas terminadas.
// Retorno: NOERROR (0) ou ERROR (<0)
int task_destroy(struct task_t *task) {

}

// transfere a cpu da tarefa atual para outra tarefa;
// se task == NULL, transfere para a tarefa que a criou.
// ignora sem erro se "task" já tiver terminado.
// Retorno: NOERROR (0) ou ERROR (<0)
int task_switch(struct task_t *task) {

}

// informa o ID de uma tarefa (ou da tarefa atual se NULL)
int task_id(struct task_t *task) {

}

// informa o nome de uma tarefa (ou da tarefa atual se NULL)
char *task_name(struct task_t *task) {

}
