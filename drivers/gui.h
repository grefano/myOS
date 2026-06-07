#pragma once
#include "../drivers/draw.c"
#include "../drivers/cursor.h"
#include "../drivers/window.h"
void draw_screen(struct pixelbuffer* pb){

  //draw_text("hello", 5, 200, 300);
  //ssfn_render(&ssfn_ctx, &ssfn_dst, "hellp");



  draw_text("tem coisa q tlgd", 20, 300, 300, 0xFFFFFFFF);
  draw_text("tem outras q tbm é foda", 10, 50, 400, 0xFFFF00FF);
  struct Window window = window_create(pb, 50, 50);
  window.get_pos_surface = window_surface_example1;
  window_draw(&window);
  cursor_start(pb);
  cursor_draw();

}
