#define TINY_ANSI_IMPLEMENTATION
#include "tinyansi.h"

int main() {
    tansi_init();

    // Header
    tansi_styleprintln("=== Tiny_ANSI Demo ===", 
                       TANSI_CYAN, TANSI_BG_DEFAULT, TANSI_EFFECT_BOLD);

    // Colored messages
    tansi_println("This is a green success message.", TANSI_GREEN);
    tansi_println("This is a yellow warning message.", TANSI_YELLOW);
    tansi_println("This is a red error message.", TANSI_RED);

    // Styled text
    tansi_styleprintln("Bold,Magenta Text", 
      TANSI_MAGENTA, TANSI_BG_DEFAULT, TANSI_EFFECT_BOLD);

    // Background colors
    //
    tansi_enable_bgcolor(TANSI_BG_BLUE);
    tansi_println("White text on Blue background", TANSI_WHITE);
    tansi_disable_bgcolor();

    tansi_enable_bgcolor(TANSI_BG_MAGENTA);
    tansi_println("Yellow text on Magenta background", TANSI_YELLOW);
    tansi_disable_bgcolor();

    // Logging simulation
    tansi_log(TANSI_INFO, "Server started successfully.");
    tansi_log(TANSI_WARN, "Memory usage is high.");
    tansi_log(TANSI_ERROR, "Failed to open config file.");


    // Fatal error demonstration
    // Uncomment to test (program exits)
    // tansi_fatal("FATAL", "Unable to connect to database!", __FILE__, __LINE__);

    // Footer
    tansi_styleprintln("=== End of Demo ===", 
                       TANSI_CYAN, TANSI_BG_DEFAULT, TANSI_EFFECT_BOLD);

    return 0;
}

