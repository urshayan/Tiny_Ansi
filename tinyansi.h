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


typedef enum {

    TANSI_INFO,
    TANSI_WARN,
    TANSI_ERROR,
    TANSI_DEBUG

} tansi_level;


//// funtionsssssssssssssssssssssssssssss
void tansi_print(const char* msg , tansi_color color);
void tansi_println(const char* msg , tansi_color color);
void tansi_printf(tansi_color color , const char* fmt , ...);
void tansi_log(tansi_level level , const char* fmt, ...);
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
#include <stdarg.h>
#include <time.h>
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

void tansi_printf(tansi_color color, const char* fmt,...)
{
    

    if (color < 0 || color >= TANSI_COLOR_COUNT)
      color = TANSI_RESET;

  va_list args;
  
  va_start(args,fmt);

  printf("%s" , tansi_map[color]);
  vprintf(fmt, args);
  printf("%s", tansi_map[TANSI_RESET]);

  va_end(args);

}

void tansi_log(tansi_level level , const char* fmt , ...)
{
    
    char timebuf[9];
////// time stamppppp!
    time_t now = time(NULL);
    struct tm* t = localtime(&now);
    strftime(timebuf , sizeof(timebuf) , "%H:%M:%S" , t);
    switch (level){
      case 0:
        tansi_printf(TANSI_GREEN , "[%s] [%s] " , timebuf, "INFO");
        break;
      case 1:
         tansi_printf(TANSI_RED , "[%s] [%s] " , timebuf, "WARN");
         break;
      case 2:
          tansi_printf(TANSI_MAGENTA , "[%s] [%s] " , timebuf, "ERROR");
          break;
      case 3:
           tansi_printf(TANSI_CYAN , "[%s] [%s] " , timebuf, "DEBUG");
           break;
      default:
           printf("Log Failed! \n");
    }
    
    // now we print the message body

    va_list args;

    va_start(args , fmt);
    vprintf(fmt,args);
    va_end(args);

    printf("\n");

}




#endif // TINY_ANSI_IMPLEMENTATION

