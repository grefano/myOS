#pragma once

typedef struct Context{
  uint32_t edi;
  uint32_t esi;
  uint32_t ebx;
  uint32_t ebp; // extended base pointer - base da stack
  uint32_t eip;
  //uint32_t eip; // instruction
};
