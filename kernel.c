#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "libc.h"
#include "string.h"
#define SSFN_MAXLINES 32
#define SSFN_IMPLEMENTATION
#include "ssfn.h"
#include "./drivers/draw.h"
#include "./drivers/cursor.h"
extern void gdt_init(void);
extern void idt_init(void);
extern void teste(void);
extern void PIC_remap(int,int);
/* Check if the compiler thinks you are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif
extern uint32_t end;
uint32_t heap_start;
uint32_t heap_end;
void init_heap(){
   heap_start = (uint32_t)&end;//((uint32_t)&end + 3) & -3;
  heap_end = heap_start;
}



uint32_t hex_lerp(uint32_t start, uint32_t end, float lerp){
  return start + ((float)end - (float)start) * lerp;
}

uint32_t screenw = 0;
uint32_t screenh = 0;
uint32_t* pixels = 0;



void draw_rect(uint32_t* pixels, uint32_t col1, uint32_t col2, uint32_t col3, uint32_t col4, int xs, int ys, int w, int h){
  xs = xs-w/2;
  ys = ys-h/2;

  for(int x = 0; x < w; x++){

    for(int y = 0; y < h; y++){
      int i = (y+ys) * screenw + (x+xs);
      pixels[i] =  hex_lerp(hex_lerp(col1, col2, (float)x / (float)w), hex_lerp(col3, col4, (float)x / (float)w), (float)y / (float)h);
    }    
  }

}
void draw_screen(){

  for(int x = 0; x < screenw; x++){
    for(int y = 0; y < screenh; y++){

      int i = y * screenw + x;
      pixels[i] = 0x001C1c1c;
    }
  }

  draw_rect(pixels, 0x00FF0000, 0x00FFFF00, 0x000000FF, 0x0000FF00,  screenw/2, screenh/2, screenw/2, screenw/2);
}


//uint32_t teste = 6;
void kernel_main(unsigned int magic, unsigned int* mb_info) 
{

  PIC_remap(0x20, 0xA0);
  gdt_init();
  idt_init();
 init_heap();


  //teste();n
  //return;
  //__asm__ volatile ("movl $6, %0)" : "=r"(teste)  );
  //teste();
  //return;
  /* pula os primeiros 8 bytes (total_size + reserved) */
    struct mb2_tag *tag = (struct mb2_tag *)((uint8_t *)mb_info + 8);

  while (tag->type != 0) {
    if (tag->type == 8) { /* framebuffer */
      struct mb2_tag_framebuffer *fb = (struct mb2_tag_framebuffer *)tag;
      pixels = (uint32_t *)(uint32_t)fb->addr;
      screenw = fb->width;
      screenh = fb->height;
      
      pixels[0] = 0x00FFFFFF;
      pixels[1] = 0x00FFFFFF;


 draw_start(screenw, screenh, fb->pitch, pixels); 
      //draw_text("hello", 5, 200, 300);
      //ssfn_render(&ssfn_ctx, &ssfn_dst, "hellp");
      


      draw_text("tem coisa q tlgd", 20, 300, 300, 0xFFFFFFFF);
      draw_text("tem outras q tbm é foda", 10, 50, 400, 0xFFFF00FF);
      cursor_start(fb);
      cursor_draw();
    }
    /* avança para a próxima tag (alinhada em 8 bytes) */
    tag = (struct mb2_tag *)((uint8_t *)tag + ((tag->size + 7) & ~7));
  }
  ssfn_free(&ssfn_ctx);
  
}
