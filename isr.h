#pragma once
#include "./drivers/input.h"
void handler_keyboard(){
  io_wait();
  uint8_t scancode = inb(PORT_DATA);
  outb(0x20, 0x20);
}
