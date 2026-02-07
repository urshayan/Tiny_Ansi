#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define TINY_ANSI_IMPLEMENTATION
#include "tinyansi.h"

int main() {
    tansi_init();
    srand(time(NULL));

    tansi_canvas* c = tansi_canvas_create(30, 15);

    for (int y = 0; y < c->height; y++) {
        for (int x = 0; x < c->width; x++) {
            tansi_color col = static_cast<tansi_color>(TANSI_RED + (rand() % 6)); // random bright color
            tansi_draw_pixel(c, x, y, col);
        }
    }

    tansi_canvas_present(c);

    tansi_print("This noise pattern was made by TINY ANSI --- no external libs" , TANSI_RED);
    printf("\nPress Enter to exit...");
    getchar();
    tansi_canvas_destroy(c);
}

