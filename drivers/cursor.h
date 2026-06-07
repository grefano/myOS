#pragma once
#include "./draw.h"

struct Cursor{
  int x;
  int y;
  struct pixelbuffer* fb;
};
struct Cursor cursor = {50, 50, 0};

void cursor_start(struct pixelbuffer* fb){
  cursor.fb = fb;
}
void cursor_draw(){
  int size = 50;
  uint32_t* pixels = (uint32_t*)(uint32_t)(cursor.fb->addr);
  for (size_t x = 0; x < size; x++){
    for(size_t y = 0; y < size; y++){
      size_t xs = cursor.x + x;
      size_t ys = cursor.y + y;
      size_t i = xs + ys * (cursor.fb->width);
   


      size_t d = (x*x + y*y) / 2; 
      uint32_t col = pixels[i] | (d < size/2 ? 0xFFFF0000 : 0xFF000000);
      pixels[i] = col;
      
    }
  
  }
  

}
