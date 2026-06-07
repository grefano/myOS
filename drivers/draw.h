
#pragma once
#include "../libc.h"
#include "../ssfn.h"
#include "../drivers/window.h"
ssfn_font_t *ssfn_src;
ssfn_buf_t ssfn_dst;
ssfn_t ssfn_ctx = {0};
extern unsigned char _binary_lanapixel_sfn_start[];
void draw_start(struct pixelbuffer* pb){
  
  ssfn_load(&ssfn_ctx, (ssfn_font_t*)_binary_lanapixel_sfn_start);


  
  ssfn_dst.w = pb->width;                          /* width */
  ssfn_dst.h = pb->height;                           /* height */
  ssfn_dst.p = pb->pitch;                          /* bytes per line */

  ssfn_dst.ptr = (uint8_t*)pb->addr;
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

uint32_t hex_lerp(uint32_t start, uint32_t end, float lerp){
  return start + ((float)end - (float)start) * lerp;
}

void draw_rect(struct pixelbuffer* fb, uint32_t col1, uint32_t col2, uint32_t col3, uint32_t col4, int xs, int ys, int w, int h){
  xs = xs-w/2;
  ys = ys-h/2;

  for(int x = 0; x < w; x++){

    for(int y = 0; y < h; y++){
      int i = (y+ys) * fb->width + (x+xs);
      fb->addr[i] =  hex_lerp(hex_lerp(col1, col2, (float)x / (float)w), hex_lerp(col3, col4, (float)x / (float)w), (float)y / (float)h);
    }    
  }

}
