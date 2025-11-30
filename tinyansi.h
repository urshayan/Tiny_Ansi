#ifndef TINY_ANSI_H
#define TINY_ANSI_H

#ifdef __cplusplus
extern "C" {
#endif

// ==========================
// PUBLIC API DECLARATIONS
// ==========================

// Declare your functions here
// Example:
// void tiny_ansi_print(const char* msg, int color);
// int  tiny_ansi_version(void);


  // mapping enums to the array!
typedef enum {

    TANSI_RESET,
    TANSI_RED,
    TANSI_GREEN,
    TANSI_YELLOW,
    TANSI_BLUE,
    TANSI_MAGENTA,
    TANSI_CYAN,
    TANSI_WHITE,
    TANSI_COLOR_COUNT
      /// more to addd!!!!!!
}tansi_color;

static const char* tansi_map[TANSI_COLOR_COUNT] = {
    "\033[0m",   // RESET
    "\033[31m",  // RED
    "\033[32m",  // GREEN
    "\033[33m",  // YELLOW
    "\033[34m",  // BLUE
    "\033[35m",  // MAGENTA
    "\033[36m",  // CYAN
    "\033[37m"   // WHITE
};

//// funtionsssssssssssssssssssssssssssss
void tansi_print(const char* msg , tansi_color color);
void tansi_println(const char* msg , tansi_color color);

#ifdef __cplusplus
}
#endif

#endif // TINY_ANSI_H


// ==========================
// IMPLEMENTATION SECTION
// ==========================

#ifdef TINY_ANSI_IMPLEMENTATION

#include <stdio.h>
#include <assert.h>
// Define your functions here
// Example:
// void tiny_ansi_print(const char* msg, int color) { }

void tansi_print(const char* msg, tansi_color color)
{
    assert(msg != NULL);
    if (color < 0 || color >= TANSI_COLOR_COUNT)
      color = TANSI_RESET;

  printf("%s%s%s" , tansi_map[color] , msg , tansi_map[TANSI_RESET]);
}

void tansi_println(const char* msg , tansi_color color)
{
    assert(msg != NULL);

    if (color < 0 || color >= TANSI_COLOR_COUNT)
      color = TANSI_RESET;

    printf("%s%s%s" , tansi_map[color] , msg , tansi_map[TANSI_RESET]);
    printf("\n");

}






#endif // TINY_ANSI_IMPLEMENTATION

