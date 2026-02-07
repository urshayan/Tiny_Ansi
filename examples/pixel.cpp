#define TINY_ANSI_IMPLEMENTATION
#include "tinyansi.h"


int main()
{
    tansi_init();

    tansi_graphics_begin();

    // draw shit pixels here!
    //

    for (int i = 0; i < 20; i++) {
        tansi_draw_pixel(10+i, 5, TANSI_GREEN);
        tansi_draw_pixel(10+i, 6, TANSI_CYAN);
    }

    getchar();// wait
    tansi_graphics_end();



  

return 0;

}

