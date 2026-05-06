#pragma once
#include "../inlineas.h"
#include <stdint.h>

#define REG_CMD 0x64
#define PORT_DATA 0x60
#define REG_STATUS 0x64

void init_ps2(){

  
  
  uint8_t r;
  outb(REG_CMD, 0xAD); // disable keyboard
  io_wait();
  outb(REG_CMD, 0xA7); // disable mouse
  io_wait();

  inb(PORT_DATA); // flush
  io_wait();
  
  outb(REG_CMD, 0x20); // set config byte
  io_wait();
  uint8_t config_byte = inb(PORT_DATA);
  io_wait();
  config_byte &= 0b01010101;
  outb(REG_CMD, 0x60);
  io_wait();
  outb(PORT_DATA, config_byte);
  io_wait();

  // test ps2 controller
  outb(REG_CMD, 0xAA);
  io_wait();
  r = inb(PORT_DATA); // 254 FE
  if (r != 0x55) return;
  io_wait();

  outb(REG_CMD, 0xAB);
  io_wait();
  r = inb(PORT_DATA);
  if (r != 0x0) return;
  io_wait();

  // enable port 1
  outb(REG_CMD, 0xAE);
  io_wait();

  // reset device of port 1
  outb(REG_CMD, 0xFF);
  io_wait();
  if (inb(PORT_DATA) != 0xFA) return;
  io_wait();

}
