/*                   _______  _        _______ _________
\__   __/\__   __/( (    /||\     /|  (  ___  )( (    /|(  ____ \\__   __/
   ) (      ) (   |  \  ( |( \   / )  | (   ) ||  \  ( || (    \/   ) (   
   | |      | |   |   \ | | \ (_) /   | (___) ||   \ | || (_____    | |   
   | |      | |   | (\ \) |  \   /    |  ___  || (\ \) |(_____  )   | |   
   | |      | |   | | \   |   ) (     | (   ) || | \   |      ) |   | |   
   | |   ___) (___| )  \  |   | |     | )   ( || )  \  |/\____) |___) (___
   )_(   \_______/|/    )_)   \_/     |/     \||/    )_)\_______)\_______/
                                                                          
*/ 


#ifndef TINY_ANSI_H
#define TINY_ANSI_H

#ifdef __cplusplus
extern "C" {
#endif

// ==========================
// PUBLIC API DECLARATIONS
// ==========================

  static int g_graphics_enabled = 0;

  

  // mapping Foreground Colors 
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
    "\033[39m",   // RESET
    "\033[31m",  // RED
    "\033[32m",  // GREEN
    "\033[33m",  // YELLOW
    "\033[34m",  // BLUE
    "\033[35m",  // MAGENTA
    "\033[36m",  // CYAN
    "\033[37m"   // WHITE
};

//////// -------------------------------------
typedef enum {

    TANSI_INFO,
    TANSI_WARN,
    TANSI_ERROR,
    TANSI_DEBUG

} tansi_level;


/////// -------------------------------------------- 

// mapping background colors

typedef enum {
    TANSI_BG_DEFAULT,
    TANSI_BG_RED,
    TANSI_BG_GREEN,
    TANSI_BG_YELLOW,
    TANSI_BG_BLUE,
    TANSI_BG_MAGENTA,
    TANSI_BG_CYAN,
    TANSI_BG_WHITE,
    TANSI_BG_COUNT
} tansi_bg;

static const char* tansi_bg_map[TANSI_BG_COUNT] = {
    "\033[49m", // default
    "\033[41m", // red
    "\033[42m", // green
    "\033[43m", // yellow
    "\033[44m", // blue
    "\033[45m", // magenta
    "\033[46m", // cyan
    "\033[47m"  // white
};

//// --------------------------------------------------------  

/// Mapping Effectssss

typedef enum {
    TANSI_EFFECT_RESET = 0,
    TANSI_EFFECT_BOLD,
    TANSI_EFFECT_DIM,
    TANSI_EFFECT_UNDERLINE,
    TANSI_EFFECT_BLINK,
    TANSI_EFFECT_REVERSE,
    TANSI_EFFECT_COUNT
}tansi_effects;

static const char* tansi_effect_map[TANSI_EFFECT_COUNT] = {

    "\033[0m",  // reset
    "\033[1m",  // bold
    "\033[2m",  // dim
    "\033[4m",  // underline
    "\033[5m",  // blink (not supported everywhere)
    "\033[7m"   // reverse
};
/////-------------------------------------------------------------------  

#define RESET "\033[0m"
// --------------------------------------------------------------------- 
// structs -- for the graphics!@
typedef struct {
  int width;
  int height;
  tansi_color* buffer;
}tansi_canvas;



//// funtionsssssssssssssssssssssssssssss
void tansi_print(const char* msg , tansi_color color);
void tansi_println(const char* msg , tansi_color color);
void tansi_printf(tansi_color color , const char* fmt , ...);
void tansi_log(tansi_level level , const char* fmt, ...);
void tansi_init(void);
void tansi_enablecolor(tansi_color color);
void tansi_disablecolor();
void tansi_enable_bgcolor(tansi_bg bg);
void tansi_disable_bgcolor();
void tansi_eprint(const char* msg ,  tansi_effects effect);   // effect print 
void tansi_eprintln(const char* msg , tansi_effects effect);
void tansi_eprintf(tansi_effects effect , const char* fmt , ...);
void tansi_styleprint(const char* msg , tansi_color color, tansi_bg bg , tansi_effects effect);
void tansi_styleprintln(const char* msg , tansi_color color, tansi_bg bg , tansi_effects effect);
void tansi_fatal(const char* tag, const char* msg, const char* file , int line);
void tansi_render_file(const char* filepath);
void tansi_render_style(const char* filepath, tansi_color fg, tansi_bg bg, tansi_effects effect);
void tansi_move_cursor(int row, int col);
void tansi_draw_pixel(tansi_canvas* c, int x, int y, tansi_color color);
void tansi_graphics_begin(void);
void tansi_graphics_end(void);
void tansi_canvas_destroy(tansi_canvas* c);
void tansi_canvas_clear(tansi_canvas* c , tansi_color color);
void tansi_canvas_present(const tansi_canvas* c);  // actual renderer!
void tansi_get_terminal_size(int* out_w, int* out_h);
tansi_canvas* tansi_canvas_create(int width, int height);


//#define TANSI_ASSERT(x, msg) \
//    do { \
//        if (!(x)) { tansi_fatal("ASSERT", msg, __FILE__, __LINE__); } \
//    } while(0)
#define TANSI_ASSERT(cond, msg) \
    ((cond) ? (void)0 : tansi_fatal("ASSERT", msg, __FILE__, __LINE__))



#ifdef __cplusplus
}
#endif

#endif // TINY_ANSI_H


// ==========================
// IMPLEMENTATION SECTION
// ==========================

#ifdef _WIN32
    #include <windows.h>
#endif

#ifdef TINY_ANSI_IMPLEMENTATION

#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <cstdlib>
#include <cstring>
#include <sys/ioctl.h>
#include <unistd.h>



void tansi_print(const char* msg, tansi_color color)
{
    //TANSI_ASSERT(msg != NULL, "Message Cannot be EMPTY");

    TANSI_ASSERT(msg && msg[0] != '\0', "Message is empty");
    
    if (color < 0 || color >= TANSI_COLOR_COUNT)
      color = TANSI_RESET;

  printf("%s%s%s" , tansi_map[color] , msg , tansi_map[TANSI_RESET]);
}

void tansi_println(const char* msg , tansi_color color)
{
    //TANSI_ASSERT(msg != NULL , "Message Cannot be EMPTY");
    TANSI_ASSERT(msg && msg[0] != '\0', "Message is empty");

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

void tansi_init(void)
{
  #ifdef _WIN32
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    if (hOut == INVALID_HANDLE_VALUE) return;

    DWORD dwmode = 0;

    if (!GetConsoleMode(hOut , &dwmode)) return;
    dwmode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    //SetConsoleMode(hOut , dwmode);
    if (!SetConsoleMode(hOut, dwmode)){
      printf("Warning: ANSI colors are not supported! \n");
    }

  #endif
}

void tansi_enablecolor(tansi_color color)
{
    if (color < 0 || color >= TANSI_COLOR_COUNT) return;
    printf(tansi_map[color]);
}

void tansi_disablecolor()
{
    printf(tansi_map[TANSI_RESET]);
}

void tansi_enable_bgcolor(tansi_bg bg)
{
    if (bg < 0 || bg >= TANSI_BG_COUNT) return;
    printf(tansi_bg_map[bg]);

}

void tansi_disable_bgcolor()
{
  printf(tansi_bg_map[TANSI_BG_DEFAULT]);
}

void tansi_eprint(const char* msg , tansi_effects effect)
{
 // TANSI_ASSERT(msg != NULL , "Message Cannot be EMPTY");
  TANSI_ASSERT(msg && msg[0] != '\0', "Message is empty");
   if (effect < 0 || effect >= TANSI_EFFECT_COUNT) effect = TANSI_EFFECT_RESET;

   printf("%s%s%s" , tansi_effect_map[effect] , msg , tansi_effect_map[TANSI_EFFECT_RESET]);

}

void tansi_eprintln(const char* msg , tansi_effects effect)
{
  //TANSI_ASSERT(msg != NULL , "Message cannot be EMPTY");
  TANSI_ASSERT(msg && msg[0] != '\0', "Message is empty");
    if (effect < 0 || effect >= TANSI_EFFECT_COUNT) effect = TANSI_EFFECT_RESET;

    printf("%s%s%s" , tansi_effect_map[effect] , msg , tansi_effect_map[TANSI_EFFECT_RESET]);
    printf("/n");
}

void tansi_eprintf(tansi_effects effect, const char* fmt,...)
{
    

    if (effect < 0 || effect >= TANSI_EFFECT_COUNT)
      effect = TANSI_EFFECT_RESET;

  va_list args;
  
  va_start(args,fmt);

  printf("%s" , tansi_effect_map[effect]);
  vprintf(fmt, args);
  printf("%s", tansi_effect_map[TANSI_RESET]);

  va_end(args);

}

void tansi_styleprint(const char* msg , tansi_color color, tansi_bg bg , tansi_effects effect)
{
      //TANSI_ASSERT(msg != NULL , "Message Cannot Be EMPTY");
      TANSI_ASSERT(msg && msg[0] != '\0', "Message is empty");

      
          if (color < 0 || color >= TANSI_COLOR_COUNT)
              color = TANSI_RESET;
          if (bg < 0 || bg >= TANSI_BG_COUNT)
              bg = TANSI_BG_DEFAULT;
          if (effect < 0 || effect >= TANSI_EFFECT_COUNT)
              effect = TANSI_EFFECT_RESET;

          printf("%s%s%s%s",tansi_effect_map[effect], tansi_map[color] ,  tansi_bg_map[bg] , msg );

          printf("%s" , tansi_effect_map[TANSI_EFFECT_RESET]);

}

void tansi_styleprintln(const char* msg , tansi_color color, tansi_bg bg , tansi_effects effect)
{
      tansi_styleprint(msg,color,bg,effect);
      printf("\n");
}

void tansi_fatal(const char* tag, const char* msg, const char* file , int line)
{
      fprintf(stderr,"%s%s[FATAL %s] %s" , tansi_effect_map[TANSI_EFFECT_BOLD] , tansi_map[TANSI_GREEN] , tag , RESET );
      fprintf(stderr,"%s \n" , msg );
      fprintf(stderr,"%s Location: %s %s : %d \n", tansi_map[TANSI_BLUE] , RESET , file , line);

      fflush(stderr);

      exit(EXIT_FAILURE);

}

void tansi_render_file(const char* filepath)
{

    FILE* file;
    char buffer[1024];

    if(!filepath){
      fprintf(stderr, "[tansi] Invalid file Path (NULL) \n");
      return;
    }
    
    file = fopen(filepath, "r");
    if(!file){
        fprintf(stderr, "[tansi] Failed to open File: %s\n", filepath);
        return;
    }
    
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len-1] == '\r'){
      buffer[len-1] = '\0';
    }

    while(fgets(buffer, sizeof(buffer), file)){
      printf("%s", buffer);
    }
    
    fclose(file);
}

void tansi_render_style(const char* filepath, tansi_color fg, tansi_bg bg, tansi_effects effect)
{
    
  TANSI_ASSERT(filepath != NULL , "File Path cannot be left empty!" );

   if (fg < 0 || fg >= TANSI_COLOR_COUNT)
        fg = TANSI_RESET;
    if (bg < 0 || bg >= TANSI_BG_COUNT)
        bg = TANSI_BG_DEFAULT;
    if (effect < 0 || effect >= TANSI_EFFECT_COUNT)
        effect = TANSI_EFFECT_RESET;

    FILE* file = fopen(filepath, "r");
    if (!file) {
        perror("[tansi] Failed to open ASCII file");
        return;
    }

    char buffer[1024];
    while(fgets(buffer, sizeof(buffer), file))
{

    size_t len = strlen(buffer);
    if (len > 0 && buffer[len-1] == '\r')
    {
      buffer[len-1] = '\0';
    }
      printf("%s%s%s%s%s", 
        tansi_effect_map[effect],
        tansi_map[fg],
        tansi_bg_map[bg],
        buffer,
        tansi_effect_map[TANSI_EFFECT_RESET]

      );

}
    fclose(file);
    fflush(stdout);
}

void tansi_move_cursor(int row, int col)
{
  printf("\033[%d;%dH", row, col);
}
 // immediate mode render!
//void tansi_draw_pixel(int x, int y, tansi_color color)
//{

  //  if (!g_graphics_enabled) return;
   // if (color < 0 || color >= TANSI_COLOR_COUNT)
       // color = TANSI_RESET;

    //tansi_move_cursor(y+1, x+1);
    //printf("%s█%s", tansi_map[color], tansi_map[TANSI_RESET]);
    //fflush(stdout);
//}
//retained mode render pixel! 

void tansi_draw_pixel(tansi_canvas* c, int x, int y, tansi_color color)
{
  if(!c) return;

  if (x < 0 || y < 0 || x >= c->width || y >= c->height) return;

  c->buffer[y * c->width + x] = color;  // indexing formula == inedx = y * width + x 

}


void tansi_graphics_begin(void)
{
    g_graphics_enabled = 1;
    printf("\033[2J");            // for clear screen
    printf("\033[?25l");          // for hide cursor
    fflush(stdout);
}

void tansi_graphics_end(void)
{

  g_graphics_enabled = 0;
    printf("\033[?25h");          // show cursor
    printf("\033[0m");            // reset colors
    fflush(stdout);
}

tansi_canvas* tansi_canvas_create(int width , int height)
{
  int term_w , term_h ;// terminal width and height
  tansi_get_terminal_size(&term_w,&term_h);

  if (width > term_w ) width = term_w;
  if (height > term_h -1) height = term_h -1; // avoiddd scrolllll 



  if (width <= 0 || height <= 0) return NULL;



  tansi_canvas* c =(tansi_canvas*) malloc(sizeof(tansi_canvas));
  if(!c) return NULL;

  c->width = width;
  c->height = height;
  c->buffer = (tansi_color*)malloc(sizeof(tansi_color)* width * height);

  if(!c->buffer){
    free(c);
    return NULL;
  }

  memset(c->buffer,TANSI_RESET,sizeof(tansi_color) * width * height);
  return c;

}

void tansi_canvas_destroy(tansi_canvas* c)
{
    if(!c) return;
    free(c->buffer);
    free(c);

}

void tansi_canvas_clear(tansi_canvas* c , tansi_color color)
{
  if (!c) return;
    
  for (int i = 0; i < c->width * c->height; i++){
    c->buffer[i] = color;
  }

}

void tansi_canvas_present(const tansi_canvas* c)
{
  
  if (!c) return ;

  printf("\033[H"); // move cursor to top-left
  
  for (int y = 0; y < c->height; y++){
    for (int x = 0; x < c->width; x++){
      tansi_color col = c->buffer[y * c->width + x];
      printf("%s█", tansi_map[col]);
    }
    printf("\n");
  }
  printf("%s", tansi_map[TANSI_RESET]);
  fflush(stdout);

}

void tansi_get_terminal_size(int* out_w, int* out_h)
{
      if (!out_w || !out_h) return;

    struct winsize ws;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == 0) {
        *out_w = ws.ws_col;
        *out_h = ws.ws_row;
    } else {
        *out_w = 80;  // safe fallback
        *out_h = 24;
    }

}



#endif // TINY_ANSI_IMPLEMENTATION

