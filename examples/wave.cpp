#include <stdio.h>
#include <unistd.h>  // for usleep
#include <math.h>    // for sin
#define TINY_ANSI_IMPLEMENTATION
#include "../tinyansi.h"

#define WIDTH 50
#define HEIGHT 15
#define FRAMES 100

int main() {
    tansi_init();

    // Create canvas
    tansi_canvas* c = tansi_canvas_create(WIDTH, HEIGHT);

    // Animation loop
    for (int frame = 0; frame < FRAMES; frame++) {
        for (int y = 0; y < HEIGHT; y++) {
            for (int x = 0; x < WIDTH; x++) {
                // Create a wave pattern using sine
                float value = sinf((x + frame) * 0.3f) + sinf((y + frame) * 0.2f);
                int color_index = (int)((value + 2) * 3) % 6; // maps to 0-5
                tansi_color col = static_cast<tansi_color>(TANSI_RED + color_index);
                tansi_draw_pixel(c, x, y, col);
            }
        }

        // Render canvas
        tansi_canvas_present(c);

        // Small delay
        usleep(60000); // 60ms ~ ~16 FPS
    }

    tansi_canvas_destroy(c);
    return 0;
}

