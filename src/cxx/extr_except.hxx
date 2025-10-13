#pragma once
#ifndef __cplusplus
#error "This header is cxx only"
#endif
#include <spdlog/spdlog.h>

namespace extr {

template <typename ITEM>
class except {
public:
  except(ITEM msg) {
    this->err = msg;
  }

  void what() const {
    spdlog::error("{}", this->err);
  }

  ITEM get() const {
    return this->err;
  }
private:
  ITEM err;
};





}



