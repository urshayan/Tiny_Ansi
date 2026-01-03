#include <iostream>


#define TINY_ANSI_IMPLEMENTATION
#include "tinyansi.h"


int main()
{
  
  tansi_render_style("test.txt", TANSI_YELLOW, TANSI_BG_RED,TANSI_EFFECT_BOLD);

  tansi_print("Hello World!" , TANSI_RED);


  return 0;
}
