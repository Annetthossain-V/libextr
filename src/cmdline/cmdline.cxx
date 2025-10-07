#include "cmdline.h"
#include "../core/config.h"
#include <cstdlib>
#include <stdexcept>
#include <cstring>

static inline bool chr_arr_contains(const char* item, const char** arr, const size_t arr_len) {
  for (size_t i = 0; i < arr_len; i++) {
    if (strcmp(arr[i], item) == 0)
      return true;
  }
  return false;
}

extern "C" extr::args_t* extr::parse_args(const int argc, const char **argv, const char** dual_args, const size_t dual_len) {
  args_t* args = (args_t*)malloc(sizeof(args_t));

  size_t args_file_cap = 16;
  args->files = (char**)malloc(sizeof(char*) * args_file_cap);
  args->files_len = 0;

  size_t options_cap = 16;
  args->option = (decltype(args->option))malloc(sizeof(*args->option) * options_cap);
  args->options_len = 0;

  for (int i = 1; i < argc; i++) {
    if (argv[i][0] != '-') {
      char* str = (char*) malloc(strlen(argv[i]) + 1);
      strcpy(str, argv[i]);
     
      if (args_file_cap < args->files_len + 2) {
        args_file_cap += 16;
        args->files = (char**) realloc(args->files, args_file_cap * sizeof(char*));
        if (!args->files) goto failure;
      }
      
      args->files[args->files_len] = str;
      args->files[args->files_len + 1] = NULL;
      args->files_len++;
    } else {
      if (options_cap < args->options_len + 2) {
        options_cap += 16;
        args->option = (decltype(args->option)) realloc(args->option, sizeof(*args->option) * options_cap);
        if (!args->option) goto failure;
      }
      
      args->option[args->options_len] = (typeof(**args->option)*) malloc(sizeof(**args->option));
      args->option[args->options_len]->flag = (char*) malloc(strlen(argv[i]) + 1);
      args->option[args->options_len]->is_arg = false;
      args->option[args->options_len]->sub_arg = NULL;
      strcpy(args->option[args->options_len]->flag, argv[i]);
  
      if (dual_args && chr_arr_contains(argv[i], dual_args, dual_len)) {
        if (i + 1 >= argc)
          goto failure;
        i++;

        args->option[args->options_len]->is_arg = true;
        args->option[args->options_len]->sub_arg = (char*) malloc(strlen(argv[i]) + 1);
        strcpy(args->option[args->options_len]->sub_arg, argv[i]);
      }

      args->options_len++;
    }
  }
  

  return args;

failure:
  if (ENABLE_EXCEPTION)
    throw std::runtime_error("Failed to parse args");
  return NULL;
}

extern "C" void extr::close_args(args_t *args) {
  for (size_t i = 0; i < args->files_len; i++)
    if (args->files[i]) free(args->files[i]);

  for (size_t i = 0; i < args->options_len; i++) {
    if (args->option[i]->sub_arg) free(args->option[i]->sub_arg);
    if (args->option[i]->flag) free(args->option[i]->flag);
    free(args->option[i]);
  }

  free(args->files);
  free(args->option);
  free(args);
  return;
}
