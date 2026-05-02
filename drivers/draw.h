
#pragma once
#include "../libc.h"
#include "../ssfn.h"

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

ssfn_font_t *ssfn_src;
ssfn_buf_t ssfn_dst;
ssfn_t ssfn_ctx = {0};
extern unsigned char _binary_lanapixel_sfn_start[];
void draw_start(int screenw, int screenh, int pitch, uint32_t* pixels){
  
  ssfn_load(&ssfn_ctx, (ssfn_font_t*)_binary_lanapixel_sfn_start);


  
  ssfn_dst.w = screenw;                          /* width */
  ssfn_dst.h = screenh;                           /* height */
  ssfn_dst.p = pitch;                          /* bytes per line */

  ssfn_dst.ptr = (uint8_t*)pixels;
  ssfn_dst.bg = 0xFF000000;/* address of the linear frame buffer */
}

void draw_text(const char* text, int size, int x, int y, unsigned int color){
  
  ssfn_src = (ssfn_font_t*)_binary_lanapixel_sfn_start;
  ssfn_dst.x = x;
  ssfn_dst.y = y;
  ssfn_dst.fg = color;                     /* foreground color */
  
  int r = ssfn_select(&ssfn_ctx, SSFN_FAMILY_ANY, NULL, SSFN_STYLE_REGULAR, size);
  if (r != 0) {return;}
  
  const char* str = text; 
  while(*str) {
    int r = ssfn_render(&ssfn_ctx, &ssfn_dst, str);
    if(r < 0) break;
    str += r;
  }
}


