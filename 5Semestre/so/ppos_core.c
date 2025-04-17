#include <stdlib.h>
#include <stdio.h>
#include <ucontext.h>
#include "ppos.h"

#define STACKSIZE 64*1024	/* tamanho de pilha das threads */

static task_t *CurrentTask;
static task_t MainTask;
static int taskCounter = 0;


# define PRONTA 0
# define EXECUTANDO 1
# define TERMINADA 2

void ppos_init() {
    setvbuf (stdout, 0, _IONBF, 0) ;
    

    getcontext(&(MainTask.context));
    MainTask.id = 0;
    MainTask.status = PRONTA;
    MainTask.prev = NULL;
    MainTask.next = NULL;
    CurrentTask = &MainTask;
}

int task_init (task_t *task, void (*start_routine)(void *),  void *arg) {
    getcontext(&(task->context));

    char *stack = malloc (STACKSIZE) ;
    if (stack)
    {
       task->context.uc_stack.ss_sp = stack ;
       task->context.uc_stack.ss_size = STACKSIZE ;
       task->context.uc_stack.ss_flags = 0 ;
       task->context.uc_link = 0 ;
    }
    else
    {
       perror ("Erro na criação da pilha: ") ;
       exit (1) ;
    }

    taskCounter++;
    task->id = taskCounter;

    task->status = PRONTA;

    makecontext(&(task->context), (void (*)(void))start_routine, 1, arg);

    return task->id;
}

int task_switch (task_t *task) {
    if (task == NULL) 
	return -1;

    task_t *oldTask = CurrentTask;

    if (oldTask != &MainTask)
	oldTask->status = PRONTA;

    CurrentTask = task;
    task->status = EXECUTANDO;

    swapcontext(&(oldTask->context), &(task->context));
    return 0;
}

void task_exit(int exit_code) {
    CurrentTask->status = TERMINADA;
    task_switch(&MainTask);
}

int task_id() {
    return CurrentTask->id;
}
