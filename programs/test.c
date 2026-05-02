

#include "../libc.h"
#include "../drivers/draw.h"
int main(){
  
  char* strtest = malloc(sizeof(char) * 4);
  strtest[0] = 'T';
  strtest[1] = 'e';
  strtest[2] = 's';
  strtest[3] = '\0';
  //const char *str = "Hello samuel";
  const char* str = strtest; 
  //while(*str) {
  //  int r = ssfn_render(&ssfn_ctx, &ssfn_dst, str);
  //  if(r < 0) break;
  //  str += r;
  //}
  draw_text(str);
  free(strtest);
}
