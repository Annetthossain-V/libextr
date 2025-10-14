#pragma once
#ifndef __cplusplus
#error "Cxx only header"
#endif
namespace extr {

template<typename T1, typename T2>
union pair_union {
  T1 first;
  T2 second;
};

template<typename T1, typename T2>
pair_union<T1, T2> make_pair_union(T1 first, T2 second) {
  return {first, second};
}


}
