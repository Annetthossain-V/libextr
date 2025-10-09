#pragma once
#include <stdbool.h>

#ifndef __unix__
#error "Target os not supported"
#endif

#ifdef __cplusplus
namespace extr {
extern "C" {
#endif

bool exec_cmd(const char* cmd, const bool wait, int* code);

#ifdef __cplusplus
} } 
#endif
