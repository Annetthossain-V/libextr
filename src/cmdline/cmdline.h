#pragma once
#include <stdlib.h>
#include <stdbool.h>

#ifdef __cplusplus
namespace extr {
extern "C" {
#endif

struct args {
  char** files;
  struct {
    char* flag;
    char* sub_arg;
    bool is_arg;
  } **option;

  size_t files_len;
  size_t options_len;
} __attribute__((packed));
typedef struct args args_t;

args_t* parse_args(const int argc, const char** argv, const char** dual_args, const size_t dual_len);
void close_args(args_t* args);

#ifdef __cplusplus
} }
#endif
