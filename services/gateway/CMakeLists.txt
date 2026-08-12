add_executable(mitra-gateway main.cc)

target_compile_features(mitra-gateway PRIVATE cxx_std_20)

target_include_directories(mitra-gateway PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
