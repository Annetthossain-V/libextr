#include "init.h" 
#include "config.h" 

void extr::extr_init() {
  ENABLE_EXCEPTION = false;
  ENABLE_LOG_CXX = true;
}

void extr::extr_finalize() {
  ENABLE_LOG_CXX = true;
  ENABLE_EXCEPTION = false;
}
