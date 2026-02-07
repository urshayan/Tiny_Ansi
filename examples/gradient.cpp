#include <stdio.h>

#define TINY_ANSI_IMPLEMENTATION
#include "../tinyansi.h"

int main() {
    tansi_init();
    tansi_canvas* c = tansi_canvas_create(30, 15);

    // Diagonal gradient: red → yellow → green
    for (int y = 0; y < c->height; y++) {
        for (int x = 0; x < c->width; x++) {
            int color_index = (x + y) % 6;

            tansi_color col = static_cast<tansi_color>(TANSI_RED + color_index); // assumes enum order
                                                                                
            tansi_draw_pixel(c, x, y, col);
        }
    }

    tansi_canvas_present(c);
    tansi_print("This gradient pattern was made by TINY ANSI -- no external libs!", TANSI_RED);
    printf("\nPress Enter to exit...");
    getchar();
    tansi_canvas_destroy(c);
}
