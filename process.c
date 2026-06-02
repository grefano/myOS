//#ifdef LIBC_H
  #include "libc.h"
#include "proc.h"
#define QTD_PROC 5
//#endif
enum procstate{
  UNUSED, RUNNING, ZOMBIE
};
typedef struct Proc{
  struct Context* ctx;
  enum procstate state;
};



struct Proc* tasks[QTD_PROC] = {0, 0, 0, 0, 0};

#define STACK_SIZE 4096
struct Context* task_create(void(*start)()){
  uint8_t *stack = malloc(STACK_SIZE);
  uint32_t *sp = (uint32_t*)(stack + STACK_SIZE);

  *(--sp) = (uint32_t)start;
  *(--sp) = 0;
  *(--sp) = 0;
  *(--sp) = 0;
  *(--sp) = 0;

  return (struct Context*)sp;
};


struct Proc* proc_create(void(*start)()){
  struct Context* ctx = task_create(start);
  struct Proc* proc = malloc(sizeof(struct Proc));
  proc->ctx = ctx;
  proc->state = UNUSED;
  for(int i = 0; i < QTD_PROC; i++){
    if (tasks[i] == 0 || tasks[i]->state == ZOMBIE){
      free(tasks[i]);
      tasks[i] = proc; 
    }
  }
}

void swtch(struct Context**, struct Context*);

extern void teste_task1();
extern void teste_task2();
extern struct Context* task1;
extern struct Context* task2;

extern struct Context* ctxSched;

//struct Context* myctx = 0;
static int a = 0;
void sched(){ 
  for(uint8_t i = 0; i < QTD_PROC; i++){
    if (tasks[i]->state == UNUSED){
      swtch(&ctxSched, tasks[i]->ctx);
    }
  }
  /*if (a == 0){
    a++;
    swtch(&ctxSched, task2);
  }
  if (a == 1){
    a++;
    swtch(&ctxSched, task1);
  }
  if (a == 2){
    a++;
    swtch(&ctxSched, task2);
  }*/
}

