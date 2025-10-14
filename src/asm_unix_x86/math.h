#pragma once
#include <stdint.h>

#if !defined(__unix__) && !defined(__x86_64__)
#error "unsupported target"
#endif

#ifdef __cplusplus
namespace extr {
extern "C" {
#endif

double pow_extr(double num, unsigned int expo);
uint64_t swap_endian64(uint64_t val);
uint32_t swap_endian32(uint32_t val);
uint16_t swap_endian16(uint16_t val);

#ifdef __cplusplus
} }
#endif
