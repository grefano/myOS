#pragma once
#include "string.h"
typedef struct block_t{
  size_t size;
  int free;
  struct block_t *next;
} block_t;

extern uint32_t heap_start;
extern uint32_t heap_end;

block_t* find_free_block(size_t size){
  if (heap_start == heap_end) return NULL;
  block_t* current = (block_t*)heap_start ;
  while(current){
    if(current->free && current->size >= size){
      return current;
    }
    current = current->next;
  }
  return NULL;
}
block_t* request_space(size_t size){
  heap_end = (heap_end + 3) & -3;
  block_t* block = (block_t*)heap_end;
    block->size = size;
    block->free = 0;
    block->next = NULL;
    heap_end += sizeof(block_t) + size;
    return block;
}
void* malloc(size_t size){
  block_t* block = find_free_block(size);

  if(!block){
    block = request_space(size);
  }
  block->free = 0;
  return (void*)(block+1);
}
void free(void* ptr){
  if (!ptr) return;

  block_t* block = (block_t*)ptr - 1;
  block->free = 1;
}

void* realloc(void* ptr, size_t size){
  if(!ptr){
    return malloc(size);
  }
  if(size == 0){
    free(ptr);
    return NULL;
  }
  block_t* block = (block_t*) ptr - 1;
  if(block->size >= size){
    return ptr;
  }


  void* new_ptr = malloc(size);
  if (!new_ptr) return NULL;
  memcpy(new_ptr, ptr, block->size);
  free(ptr);
  return new_ptr;
}
