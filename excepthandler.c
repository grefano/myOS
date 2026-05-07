#include "./drivers/input.h"
void exception_handler(void);
void exception_handler(){
  __asm__ volatile ("cli; hlt");
}


void handler_keyboard(){
  io_wait();
  uint8_t scancode = inb(PORT_DATA);
  outb(0x20, 0x20);
}
void handler_mouse(){
  io_wait();
  outb(0x20,0x20);
}

void handler_pic(){
  outb(0x20, 0x20);
}
