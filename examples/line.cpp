#define TINY_ANSI_IMPLEMENTATION
#include "../tinyansi.h"

int main()
{

    const int width = 50;
    const int height = 30;

  tansi_canvas* c = tansi_canvas_create(width,height);
 tansi_canvas_clear(c, TANSI_BLUE); 


  //tansi_canvas_clear(c, TANSI_RED);
    
  if (c){

         tansi_draw_line(c,3,3,10,20,TANSI_RED);
      }


  tansi_canvas_present(c);
  
  tansi_canvas_destroy(c);

  tansi_print("We just drawed something", TANSI_GREEN);
  return 0;
}
