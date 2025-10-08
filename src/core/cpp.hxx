#pragma once
#ifdef __cplusplus
#include <functional>
#include <type_traits>
#include <utility>
#include <cstdio>
#include <cstdlib>
#include <exception>

namespace {

template <typename Func, typename... Args>
auto call_except(Func&& func, Args&&... args) -> std::invoke_result_t<Func, Args...> {
  using R = std::invoke_result_t<Func, Args...>;

  try {
    if constexpr (std::is_void_v<R>) {
      std::invoke(std::forward<Func>(func), std::forward<Args>(args)...);
      return;
    } else {
      return std::invoke(std::forward<Func>(func), std::forward<Args>(args)...);
    }
  } catch (const std::exception& e) {
    std::fprintf(stderr, "[Exception] %s\n", e.what());
    std::exit(EXIT_FAILURE);
  } catch (...) {
    std::fprintf(stderr, "[Exception] Unknown-Type\n");
    std::exit(EXIT_FAILURE);
  }
}

}
#endif
