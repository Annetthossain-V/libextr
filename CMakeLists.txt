cmake_minimum_required(VERSION 3.20)
project(extr C CXX ASM)

file(GLOB SRCS "src/string/*.c" "src/string/*.cxx" "src/cmdline/*.cxx" "src/core/*.c" "src/io/*.cxx"
                "src/os/unix/*.c" "src/asm_unix_x86/*.s")

add_library(${PROJECT_NAME} SHARED ${SRCS})

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

target_compile_options(${PROJECT_NAME} PRIVATE
  $<$<CONFIG:Debug>: -g -O0 -Wall -Wextra>
  $<$<CONFIG:Release>: -O3 -DNDEBUG -fstack-protector -mtune=native -march=x86-64-v2>
)

target_link_options(${PROJECT_NAME} PRIVATE
  -L/usr/local/lib/
  $<$<CONFIG:Debug>: -fsanitize=address>
  $<$<CONFIG:Release>: -Wl,-O2 -flto>
)

target_link_libraries(${PROJECT_NAME} PRIVATE pthread ffi)
