#include <stdlib.h>
#include <stdio.h>
#include <ucontext.h>
#include "ppos.h"
#include "queue.h"

#define STACKSIZE 64*1024	/* tamanho de pilha das threads */

static task_t *currentTask;
static task_t mainTask;
static task_t taskYield;
static task_t dispatcherTask;
static queue_t *taskQueue;

static int userTaskCount;
static int taskCounter = 0;

# define PRONTA 0
# define EXECUTANDO 1
# define TERMINADA 2


static void dispatcherFunc();
static task_t *scheduler();

void ppos_init() {
    setvbuf (stdout, 0, _IONBF, 0) ;
    getcontext(&(mainTask.context));
    mainTask.id = 0;
    mainTask.status = PRONTA;
    mainTask.prev = NULL;
    mainTask.next = NULL;
    currentTask = &mainTask;

    taskQueue = NULL;
    task_init(&dispatcherTask, dispatcherFunc, NULL);
}

int task_init (task_t *task, void (*start_routine)(void *),  void *arg) {
    if (!task)
	return -1;

    getcontext(&(task->context));

    char *stack = malloc (STACKSIZE) ;
    if (stack) {
       task->context.uc_stack.ss_sp = stack ;
       task->context.uc_stack.ss_size = STACKSIZE ;
       task->context.uc_stack.ss_flags = 0 ;
       task->context.uc_link = 0 ;
    } else {
       perror ("Erro na criação da pilha: ") ;
       exit (1) ;
    }

    taskCounter++;
    task->id = taskCounter;

    task->status = PRONTA;

    makecontext(&(task->context), (void (*)(void))start_routine, 1, arg);

    if (start_routine != dispatcherFunc) {
	queue_append((queue_t**)&taskQueue, (queue_t*)task);
	userTaskCount++;
    }

    return task->id;
}

int task_switch (task_t *task) {
    if (task == NULL || task->status == TERMINADA) 
	    return -1;

    task_t *oldTask = currentTask;

    if (oldTask != &mainTask)
	    oldTask->status = PRONTA;

    currentTask = task;
    task->status = EXECUTANDO;

    swapcontext(&(oldTask->context), &(task->context));
    return 0;
}

void task_exit(int exit_code) {
    currentTask->status = TERMINADA;
    userTaskCount--;
    task_switch(&mainTask);
}

int task_id() {
    return currentTask->id;
}

void task_yield() {
    if (currentTask->status != TERMINADA) {
	currentTask->status = PRONTA;
	queue_append((queue_t**)&taskQueue, (queue_t*)currentTask);
    }

    task_switch(&dispatcherTask);
}

void dispatcherFunc() {
    queue_remove((queue_t**)&taskQueue, (queue_t*)dispatcherTask);

    if (currentTask == &mainTask) {
	task_t *next = scheduler();

	if (next) {
	    task_switch(next);

	    if (next->status == TERMINADA) {
		queue_remove((queue_t**)&taskQueue, (queue_t*)next);
            }
	}
    }

    exit(0);
}

void task_t *scheduler() {
    if (!taskQueue)
	return NULL;

    return (queue_size(taskQueue) > 0 ? (task*)taskQueue : NULL);
}
