#pragma once
#include <stdlib.h>
#include <stdbool.h>

#ifdef __cplusplus 
namespace extr {
extern "C" {
#endif 

#define EXTR_IO_COLOR_STYLE_RESET 0
#define EXTR_IO_COLOR_STYLE_BOLD 1
#define EXTR_IO_COLOR_STYLE_UNDERLINE 4
#define EXTR_IO_COLOR_STYLE_INVERSE 7
#define EXTR_IO_COLOR_STYLE_ITALIC 3
#define EXTR_IO_COLOR_STYLE_FAINT 2
#define EXTR_IO_COLOR_STYLE_BLINK 5
#define EXTR_IO_COLOR_STYLE_HIDDEN 8
#define EXTR_IO_COLOR_STYLE_STRIKE_THROUGH 9

void set_stdout_color(unsigned int* mode, size_t mode_len, bool fg, unsigned char r, unsigned char g, unsigned char b);

void print_color(unsigned int* mode, size_t mode_len, bool fg, unsigned char r, unsigned char g, unsigned char b, char* txt);

void reset_stdout_color();

#ifdef __cplusplus
} }
#endif 
