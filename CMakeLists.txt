cmake_minimum_required(VERSION 3.25)
project(mitra VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(MITRA_BUILD_TESTS "Build tests" ON)
option(MITRA_ENABLE_SANITIZERS "Enable ASan/UBSan" OFF)

if(MITRA_ENABLE_SANITIZERS AND CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
  add_compile_options(-fsanitize=address,undefined -fno-omit-frame-pointer)
  add_link_options(-fsanitize=address,undefined)
endif()

add_subdirectory(services/gateway)

if(MITRA_BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()
