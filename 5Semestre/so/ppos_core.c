#include <stdio.h>
#include <ucontext.h>
#include "ppos.h"

#define STACKSIZE 64*1024	/* tamanho de pilha das threads */


void ppos_init() {
    setvbuf (stdout, 0, _IONBF, 0) ;
    getcontext(&ContextMain);
    ContextCurrent = ContextMain;
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

    makecontext(&(task->context), start_routine, 1, arg);
}

int task_switch (task_t *task) {
    swapcontext(&ContextCurrent, &(task->context));
    
}