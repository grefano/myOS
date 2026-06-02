//#ifdef LIBC_H
  #include "libc.h"
#include "proc.h"
//#endif
typedef struct Proc{
  //uint32_t rsp; // topo da stack
  //uint8_t* stack; // ?
  

  
  //uint32_t esp; // extended stack pointer - topo da stack
};



struct Proc tasks[5];

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

void swtch(struct Context**, struct Context*);

extern void teste_task1();
extern void teste_task2();
extern struct Context* task1;
extern struct Context* task2;

extern struct Context* ctxSched;

//struct Context* myctx = 0;
static int a = 0;
void sched(){ 
  if (a == 0){
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
  }
}

