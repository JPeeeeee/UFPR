#include <stdlib.h>
#include <stdio.h>
#include <ucontext.h>
#include "ppos.h"
#include "ppos_data.h"
#include "queue.h"
#include <valgrind/valgrind.h>

#define STACKSIZE 64*1024

static task_t *currentTask;
static task_t mainTask;
static task_t dispatcherTask;
static queue_t *tasksQueue = NULL;
static int userTaskCount = 0;
static int taskCounter = 0;

#define PRONTA 0
#define EXECUTANDO 1
#define TERMINADA 2

void dispatcherFunc(void *arg);

void task_setprio(task_t *task, int prio) {
    int resPrio = prio;

    if (resPrio < -20)
        resPrio = -20;
    else if (resPrio > 20)
        resPrio = 20;

    if (task == NULL)
        currentTask->prio = resPrio;
    else
        task->prio = resPrio;
}

int task_getprio(task_t *task) {
    if (task == NULL)
        return currentTask->prio;
    else
        return task->prio;
}

void ppos_init() {
    setvbuf(stdout, 0, _IONBF, 0);
    
    getcontext(&mainTask.context);
    mainTask.id = 0;
    mainTask.status = PRONTA;
    mainTask.prev = NULL;
    mainTask.next = NULL;
    mainTask.prio = 0;     
    mainTask.age = 0;
    currentTask = &mainTask;

    tasksQueue = NULL;
    userTaskCount = 0;

    task_init(&dispatcherTask, dispatcherFunc, NULL);
    dispatcherTask.status = PRONTA;
}

int task_init(task_t *task, void (*start_routine)(void *), void *arg) {
    if (!task)
        return -1;

    getcontext(&task->context);

    char *stack = malloc(STACKSIZE);
    if (stack) {
        task->context.uc_stack.ss_sp = stack;
        task->context.uc_stack.ss_size = STACKSIZE;
        task->context.uc_stack.ss_flags = 0;
        task->context.uc_link = 0;
    } else {
        perror("Erro ao criar pilha: ");
        return -1;
    }

    // Registra a pilha para o valgrind
    task->vg_id = VALGRIND_STACK_REGISTER(task->context.uc_stack.ss_sp, 
                                       task->context.uc_stack.ss_sp + STACKSIZE);

    taskCounter++;
    task->id = taskCounter;
    task->status = PRONTA;
    task->prev = NULL;
    task->next = NULL;
    task->prio = 0;     
    task->age = 0;      

    makecontext(&task->context, (void (*)(void))start_routine, 1, arg);

    // Adiciona na fila de prontos (exceto dispatcher)
    if (start_routine != dispatcherFunc) {
        queue_append((queue_t**)&tasksQueue, (queue_t*)task);
        userTaskCount++;
    }

    return task->id;
}

int task_switch(task_t *task) {
    if (!task || task->status == TERMINADA)
        return -1;

    task_t *oldTask = currentTask;
    currentTask = task;

    if (oldTask->status == EXECUTANDO)
        oldTask->status = PRONTA;

    task->status = EXECUTANDO;

    swapcontext(&oldTask->context, &task->context);

    return 0;
}

void task_exit(int exit_code) {
    currentTask->status = TERMINADA;
    userTaskCount--;
    task_switch(&dispatcherTask);
}

int task_id() {
    return currentTask->id;
}

void task_yield() {
    if (currentTask->status != TERMINADA) {
        currentTask->status = PRONTA;
        // Remove tarefa atual da fila (se estiver presente)
        queue_remove((queue_t**)&tasksQueue, (queue_t*)currentTask);
        // Coloca de volta no final da fila
        queue_append((queue_t**)&tasksQueue, (queue_t*)currentTask);
    }
    task_switch(&dispatcherTask);
}

task_t *scheduler() {
    if (!tasksQueue || queue_size(tasksQueue) == 0)
        return NULL;

    task_t *nextTask = NULL;
    int melhorPrio = 21; 

    task_t *current = (task_t*)tasksQueue->next;
    task_t *start = current;
    
    do {
        int prioDinamica = current->prio - current->age;
        
        // Encontra tarefa com menor prioridade
        if (prioDinamica < melhorPrio) {
            melhorPrio = prioDinamica;
            nextTask = current;
        }

        current->age++;
        current = (task_t*)current->next;
    } while (current != start);

    return nextTask;
}

void dispatcherFunc(void *arg) {
    (void)arg;

    // Remove dispatcher da fila de prontos
    queue_remove((queue_t**)&tasksQueue, (queue_t*)&dispatcherTask);

    // Primeira ativação: muda para a primeira tarefa
    if (currentTask == &mainTask) {
        task_t *next = scheduler();
        if (next) {
            task_switch(next);
        }
    }

    // Loop do dispatcher
    while (userTaskCount > 0) {
        task_t *next = scheduler();

        if (next) {
	    // Reset da age da tarefa
            next->age = 0; 

            task_switch(next);

            if (next->status == TERMINADA) {
                queue_remove((queue_t**)&tasksQueue, (queue_t*)next);
                free(next->context.uc_stack.ss_sp);
                VALGRIND_STACK_DEREGISTER(next->vg_id);
            }
        }
    }

    exit(0);
}
