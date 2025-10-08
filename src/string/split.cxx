#include "extr_string.h"
#include <stdexcept>
#include <vector>
#include <string>
#include "../core/config.h"

std::vector<std::string> extr::split_tokens_cxx(std::string str, std::string delims) {
  std::vector<std::string> tokens;

  size_t count = 0;
  char** c_tokens = split_tokens(str.c_str(), delims.c_str(), &count);
  if (c_tokens == NULL) {
    if (ENABLE_EXCEPTION) throw std::runtime_error("unable to split tokens");
    return tokens;
  }

  tokens.reserve(count);
  for (size_t i = 0; i < count; i++) {
    tokens.push_back(c_tokens[i]);
  }

  _core_free_split_arr(c_tokens, count);
  return tokens;
}
