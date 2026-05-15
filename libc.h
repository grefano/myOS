#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "string.h"

typedef struct block_t{
  size_t size;
  int free;
  struct block_t *next;
} block_t;

block_t* find_free_block(size_t size);


block_t* request_space(size_t size);

void* malloc(size_t size);

void free(void* ptr);


void* realloc(void* ptr, size_t size);
