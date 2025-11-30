
#define TINY_ANSI_IMPLEMENTATION
#include "tinyansi.h"


int main()
{

  tansi_println("Hello", TANSI_RED);
  tansi_println("Assert test under !!" , TANSI_YELLOW);
  tansi_println("Did Assert Work???" , TANSI_CYAN);
  return 0;
}
