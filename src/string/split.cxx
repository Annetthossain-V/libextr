#include "extr_string.h"
#include <vector>
#include <string>


namespace extr {

std::vector<std::string> split_tokens_cxx(std::string str, std::string delims) {
  std::vector<std::string> tokens;

  size_t count = 0;
  char** c_tokens = split_tokens(str.c_str(), delims.c_str(), &count);

  tokens.reserve(count);
  for (size_t i = 0; i < count; i++) {
    tokens.push_back(c_tokens[i]);
  }

  _core_free_split_arr(c_tokens, count);
  return tokens;
}

}
