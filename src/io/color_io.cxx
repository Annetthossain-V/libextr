#include "color_io.h"
#include <string>
#include <iostream>
#include <cstdio>

static inline void append_mode(std::string& format, unsigned int mode) {
  format.append(std::to_string(mode));
  format.push_back(';');
}

extern "C" void extr::set_stdout_color(unsigned int *mode, size_t mode_len, bool fg, unsigned char r, unsigned char g, unsigned char b) {
  std::string format = "\x1b[";
  if (!mode) goto skip_style;

  for (size_t i = 0; i < mode_len; i++) {
    append_mode(format, mode[i]);
  }

skip_style:
  if (fg) format.append("38");
  else format.append("48");
  format.push_back(';');

  format.append("2;");
  format.append(std::to_string(r));
  format.push_back(';');
  format.append(std::to_string(g));
  format.push_back(';');
  format.append(std::to_string(b));
  format.push_back('m');

  std::cout << format;
}

extern "C" void extr::reset_stdout_color() { std::cout << "\x1b[0m"; }
