#pragma once
#include "../libc.h"
#include "./draw.h"
#include "../math.h"
struct Window{
  int x, y;
  int h, w;
  vec2 (*get_pos_surface)(struct Window* window, vec2 pos);
  struct mb2_tag_framebuffer* fb;

};
vec2 window_surface_default(struct Window* window, vec2 pos){
  return pos;
}
vec2 window_surface_example1(struct Window* window, vec2 pos){
  float p = 80.0f;
  float add = (sin((float)pos.x*2.0*PI/p))*10;
  pos.x += add; 
  return pos;
}

struct Window* window_alloc(struct mb2_tag_framebuffer* fb, int x, int y){
  struct Window* result = malloc(sizeof(struct Window));
  result->x = x;
  result->y = y;
  result->w = 320;
  result->h = 180;
  result->fb = fb;
  result->get_pos_surface = window_surface_default;
  return result;
}

struct Window window_create(struct mb2_tag_framebuffer* fb, int x, int y){
  struct Window result;
  result.x = x;
  result.y = y;
  result.w = 320;
  result.h = 180;
  result.fb = fb;
  result.get_pos_surface = window_surface_default;
  return result;
}

void window_free(struct Window* window){
  free(window);
}
uint32_t get_grid_color(uint32_t colors[], int qtd_colors, int grid_size, vec2 pos){
  vec2 l;
  l.x = pos.x % (grid_size*qtd_colors) / grid_size;
  l.y = pos.y % (grid_size*qtd_colors) / grid_size;

  return colors[(l.x + l.y) % qtd_colors];
}
uint32_t get_fade_color(uint32_t colors[], int qtd_colors, vec2 pos){
  if (qtd_colors < 2) return 0xFFFFFFFF;
  float l = (float)pos.x / 100.0f;
  if (l > 1) l = 1;
  if (l < 0) l = 0;
  uint32_t c =colors[0] +(float)(colors[1]-colors[0]) * l; 
  
  return c;
}
uint32_t window_get_pixel_color(vec2 pos){


  uint32_t colors[3] = {0xFFFF00BB, 0xFFFF00FF};// {0xFFCCCCCC, 0xFFAAAAAC, 0xFFBBCCBB};
  return get_fade_color(colors, 3, pos);
  //return get_grid_color(colors, 3, 20, pos);
}
void window_draw_buffer(struct Window* window){
  for(int x = 0; x < window->w; x++){
    for(int y = 0; y < window->h; y++){
      int i = (window->x+x) + (window->y+y) * window->fb->width;
      vec2 relpos = {x, y};
      vec2 surfpos = window->get_pos_surface(window, relpos);
      ((uint32_t*)(uint32_t)window->fb->addr)[i] = window_get_pixel_color(surfpos); 
    }
  }
}
void window_draw(struct Window* window){
    window_draw_buffer(window);
  
}
