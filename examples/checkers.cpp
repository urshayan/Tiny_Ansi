#include <stdio.h>
#include <stdlib.h>
#define TINY_ANSI_IMPLEMENTATION
#include "../tinyansi.h"  // your library

int main() {
    tansi_init(); // initialize ANSI colors
    
    // Create a canvas
    tansi_canvas* c = tansi_canvas_create(20, 10); // 20x10 canvas

    // Fill canvas with a pattern
    for (int y = 0; y < c->height; y++) {
        for (int x = 0; x < c->width; x++) {
            if ((x + y) % 2 == 0)
                tansi_draw_pixel(c, x, y, TANSI_RED);
            else
                tansi_draw_pixel(c, x, y, TANSI_GREEN);
        }
    }

    // Present the canvas
    tansi_canvas_present(c);
    
    // Pause to see the result
    
    tansi_print("This was Made By TINY ANSI -- no external Libs!" , TANSI_MAGENTA);
    printf("\nPress Enter to exit...");
    getchar();

    tansi_canvas_destroy(c);
    return 0;
}

