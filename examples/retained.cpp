#define TINY_ANSI_IMPLEMENTATION
#include "tinyansi.h"


int main()
{
  tansi_init();

  tansi_graphics_begin();

  tansi_canvas* canvas = tansi_canvas_create(50,50);

  for (int i = 0; i < 30; i++){
    tansi_canvas_clear(canvas, TANSI_RESET);
    tansi_draw_pixel(canvas, 10 , i , TANSI_RED);
  }

  tansi_canvas_present(canvas);
  tansi_canvas_destroy(canvas);

  tansi_graphics_end();
  return 0;
}
