#define TINY_ANSI_IMPLEMENTATION
#include "../tinyansi.h"


int main()
{
  
    const int width = 30;
    const int height = 30;

    tansi_canvas * c = tansi_canvas_create(width,height);
      
    if (c){
      tansi_draw_circle(c,6,6,6,TANSI_RED);
      tansi_draw_circle(c,10,6,6,TANSI_BLUE);
      tansi_draw_circle(c,14,6,6,TANSI_GREEN);
      tansi_draw_circle(c,18,6,6,TANSI_CYAN);
    }

    tansi_canvas_present(c);
    tansi_canvas_destroy(c);

  return 0;

}
