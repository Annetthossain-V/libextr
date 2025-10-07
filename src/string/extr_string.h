#pragma once
#include <stdlib.h>

#ifdef __cplusplus
#include <vector>
#include <string>

namespace extr {

std::vector<std::string> split_tokens_cxx(std::string str, std::string delims);

extern "C" {
#endif

char** split_tokens(const char* str, const char* delims, size_t* count);
void _core_free_split_arr(char** toks, size_t count);

#ifdef __cplusplus
} }
#endif
