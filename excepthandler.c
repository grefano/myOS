#include "./drivers/input.h"
extern void terminal_writestring(const char*);
extern void log(const char*);
void exception_handler(void);
void exception_handler(){
  //__asm__ volatile ("cli; hlt");
}

char keyboard_scancode_to_char(uint8_t code){
  if (code == 0x1E){
    return 'a';
  }
  if (code == 0x1F){
    return 's';
  }
  return '-';
}

void handler_keyboard(){
  io_wait();
  uint8_t scancode = inb(PORT_DATA);
  const char c = keyboard_scancode_to_char(scancode);
  char s[2];
  s[0] = c;
  s[1] = '\0';
  log(s);
  outb(0x20, 0x20);
}
void handler_mouse(){
  io_wait();
  outb(0x20,0x20);
}

void handler_pit(){
  

  outb(0x20, 0x20);
}

void handler_gpf(){
  terminal_writestring("GPF");
  log("GPF");
  //outb(0x20, 0x20);
}

void handler_pf(){
  terminal_writestring("PF");
  log("PF");
  //outb(0x20, 0x20);
}


void handler_irq(){

  outb(0x20, 0x20);
}

void handler_syscall(){

  outb(0x20, 0x20);
}
