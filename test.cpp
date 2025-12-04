#define TINY_ANSI_IMPLEMENTATION
#include "tinyansi.h"

int main()
{
    tansi_init();
  //tansi_println("Hello", TANSI_RED);
  //tansi_println("This is Tiny Ansi !!" , TANSI_YELLOW);

  //tansi_println("Tiny Like u" , TANSI_CYAN);
  
  //const char* name = "Shayan!";
// tansi_logansi_printf(TANSI_RED, "My name is %s" , name);
  
    
    //tansi_log(TANSI_INFO , "App Started!");
  //tansi_enablecolor(TANSI_YELLOW);
  //printf("Does this all makes sense? \n");
  //printf("Yes this all makes Sense!");
   ///tansi_disablecolor()
   //tansi_enable_bgcolor(TANSI_BG_RED);
   //for (int i = 0; i < 5; i++){
     //tansi_println("Hey" , TANSI_CYAN);

   //}
   //tansi_disable_bgcolor();
    
  // printf("\n This is normal Now!");
     
   // tansi_eprint("Shayan" , TANSI_EFFECT_BOLD);
   /// const char* name = "Shayaaaaaan";
    //tansi_eprintf(TANSI_EFFECT_BOLD , "My name is %s" , name);
    
      tansi_styleprint("My name is Shayan" , TANSI_RED , TANSI_BG_BLUE, TANSI_EFFECT_DIM);


  return 0;
}


