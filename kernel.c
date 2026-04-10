#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "libc.h"
#include "string.h"
#define SSFN_IMPLEMENTATION
#include "ssfn.h"
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
/* Hardware text mode color constants. */
enum vga_color {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
};

static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) 
{
	return fg | bg << 4;
}

static inline uint16_t vga_entry(unsigned char uc, uint8_t color) 
{
	return (uint16_t) uc | (uint16_t) color << 8;
}

size_t strlen(const char* str) 
{
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}

#define VGA_WIDTH   80
#define VGA_HEIGHT  25
#define VGA_MEMORY  0xB8000 

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer = (uint16_t*)VGA_MEMORY;


void terminal_initialize(void) 
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_DARK_GREY);
	
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}

void terminal_setcolor(uint8_t color) 
{
	terminal_color = color;
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) 
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}
void terminal_jump_line() 
{
  terminal_column = 0;
  terminal_row+=1;
}
void terminal_putchar(char c) 
{
	terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
	if (++terminal_column == VGA_WIDTH) {
		terminal_column = 0;
		if (++terminal_row == VGA_HEIGHT)
			terminal_row = 0;
	}
}

void terminal_write(const char* data, size_t size) 
{
	for (size_t i = 0; i < size; i++)
		terminal_putchar(data[i]);
}

void terminal_writestring(const char* data) 
{
	terminal_write(data, strlen(data));
}
struct mb2_tag {
    uint32_t type;
    uint32_t size;
};

struct mb2_tag_framebuffer {
    uint32_t type;       /* 8 */
    uint32_t size;
    uint64_t addr;       /* endereço físico do framebuffer */
    uint32_t pitch;      /* bytes por linha */
    uint32_t width;
    uint32_t height;
    uint8_t  bpp;        /* bits por pixel */
    uint8_t  fb_type;
    uint16_t reserved;
};

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



void draw_text(const char* text, int size, int x, int y){
  ssfn_dst.x = x;
  ssfn_dst.y = y;
  for(int i = 0; i < size; i++){
    ssfn_putc(text[i]);
  }
}
ssfn_font_t *ssfn_src;
ssfn_buf_t ssfn_dst;
ssfn_t ssfn_ctx = {0};
extern unsigned char _binary_u_vga16_sfn_start[];
//uint32_t teste = 6;
void kernel_main(unsigned int magic, unsigned int* mb_info) 
{
  PIC_remap(0x20, 0xA0);
  gdt_init();
  idt_init();

  ssfn_load(&ssfn_ctx, &_binary_u_vga16_sfn_start);

  //teste();
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
      

      ssfn_src = (ssfn_font_t*)_binary_u_vga16_sfn_start;

      ssfn_dst.w = fb->width;                          /* width */
      ssfn_dst.h = fb->height;                           /* height */
      ssfn_dst.p = fb->pitch;                          /* bytes per line */
      ssfn_dst.x = ssfn_dst.y =100;                /* pen position */
      ssfn_dst.fg = 0x22AA22;                     /* foreground color */
      ssfn_dst.ptr = (uint8_t*)pixels;                  /* address of the linear frame buffer */
     ssfn_dst.bg = 0x3B3733; 
      //draw_text("hello", 5, 200, 300);
      ssfn_render(&ssfn_ctx, &ssfn_dst, "hellp");
    }
    /* avança para a próxima tag (alinhada em 8 bytes) */
    tag = (struct mb2_tag *)((uint8_t *)tag + ((tag->size + 7) & ~7));
  }
  ssfn_free(&ssfn_ctx);
  
}
