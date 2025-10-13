#pragma once

#if !defined(__unix__) && !defined(__x86_64__)
#error "unsupported target"
#endif

#ifdef __cplusplus
namespace extr {
extern "C" {
#endif

double pow_extr(double num, unsigned int expo);

#ifdef __cplusplus
} }
#endif
