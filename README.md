# Tiny_ANSI

**A small, header-only C/C++ library for colorful, styled terminal output.**  

Tiny_ANSI makes it easy to print **colored messages**, **styled text**, **logs**, **fatal errors**, and even **background colors** in the terminal. Perfect for CLI tools, debugging, and interactive terminal apps.

---

## Features

- Print **colored text** easily (`tansi_print`, `tansi_printf`)  
- Add **bold, underline, and other effects** (`tansi_eprint`, `tansi_styleprint`)  
- Log messages with **levels**: INFO, WARN, ERROR, DEBUG, FATAL (`tansi_log`)  
- **Background colors** support  
- **Fatal error handler** with file & line reporting (`tansi_fatal`)  
- **Header-only**: easy to include in any project, no linking required  
- Works on **Linux/macOS** and **Windows** (enables ANSI on Windows automatically)  

---

## Getting Started

### Download

Download the header file directly:

```bash
wget https://github.com/urshayan/Tiny_Ansi/blob/main/tinyansi.h
```

Or clone the repository:

```bash
git clone https://github.com/urshayan/Tiny_Ansi
```

---

### Include in your project

```c
#define TINY_ANSI_IMPLEMENTATION
#include "tinyansi.h"
```

Call **init** at the start of your program to enable ANSI support:

```c
int main() {
    tansi_init(); // enables colors on Windows
    tansi_println("Hello, Tiny_ANSI!", TANSI_GREEN);
    return 0;
}
```

---

## Usage Examples

### Print colored messages

```c
tansi_print("Hello world", TANSI_RED);
tansi_println("This is a green line", TANSI_GREEN);
tansi_printf(TANSI_YELLOW, "Number: %d", 42);
```

### Styled & effects printing

```c
tansi_eprint("Bold message", TANSI_EFFECT_BOLD);
tansi_eprintln("Underlined message", TANSI_EFFECT_UNDERLINE);
tansi_styleprint("Styled message", TANSI_RED, TANSI_BG_BLUE, TANSI_EFFECT_BOLD);
tansi_styleprintln("Another styled message", TANSI_YELLOW, TANSI_BG_DEFAULT, TANSI_EFFECT_BLINK);
```

### Logging

```c
tansi_log(TANSI_INFO, "Info message: %s", "All systems go");
tansi_log(TANSI_WARN, "Warning: %s", "Low memory");
tansi_log(TANSI_ERROR, "Error: %s", "File not found");
```

### Fatal errors

```c
tansi_fatal("FATAL", "Critical error occurred", __FILE__, __LINE__);
```

- Prints colored, bold message  
- Shows file & line  
- Exits the program  

### Background colors

```c
tansi_enable_bgcolor(TANSI_BG_BLUE);
tansi_println("Text on blue background", TANSI_WHITE);
tansi_disable_bgcolor();
```

---

## API Reference

| Function | Description |
|----------|-------------|
| `tansi_print` | Print a message in a specific color |
| `tansi_println` | Print a colored message with newline |
| `tansi_printf` | Print a formatted colored message |
| `tansi_log` | Print log messages with levels |
| `tansi_init` | Initialize ANSI support (Windows only) |
| `tansi_enablecolor` | Enable a specific foreground color |
| `tansi_disablecolor` | Reset foreground color |
| `tansi_enable_bgcolor` | Enable background color |
| `tansi_disable_bgcolor` | Reset background color |
| `tansi_eprint` | Print message with effect (bold, underline, blink, etc.) |
| `tansi_eprintln` | Same as above but with newline |
| `tansi_eprintf` | Formatted print with effect |
| `tansi_styleprint` | Print with foreground, background, and effect |
| `tansi_styleprintln` | Same as above but with newline |
| `tansi_fatal` | Print fatal error, file & line, and exit program |

---

## Example Program

```c
#include "tinyansi.h"
#include <unistd.h> // for usleep()

int main() {
    tansi_init();

    tansi_println("Welcome to Tiny_ANSI!", TANSI_GREEN);
    tansi_styleprintln("Bold red text on yellow", TANSI_RED, TANSI_BG_YELLOW, TANSI_EFFECT_BOLD);

    tansi_log(TANSI_INFO, "This is an info message.");
    tansi_log(TANSI_WARN, "This is a warning!");
    tansi_log(TANSI_ERROR, "This is an error!");

    // Fatal example (will exit)
    // tansi_fatal("FATAL", "Something went terribly wrong", __FILE__, __LINE__);

    return 0;
}
```

---

## Installation

Just include the header in your project — no compilation or linking required.

```bash
cp tinyansi.h /your/project/include/
```

---

## License

MIT License – free to use, modify, and distribute.

---

## Downloadable

You can **download the library** and start using it immediately:

- [Download tinyansi.h](https://github.com/urshayan/Tiny_Ansi/blob/main/tinyansi.h)  

Simply include `tinyansi.h` in your project, call `tansi_init()` at the start of `main()`, and start printing colorful, styled text.

---

✅ **Tiny_ANSI is ready to use in any terminal project!**

