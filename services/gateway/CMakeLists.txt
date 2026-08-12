find_package(Drogon CONFIG REQUIRED)

add_executable(mitra-gateway
    main.cc
    HealthController.cc
)

target_compile_features(mitra-gateway PRIVATE cxx_std_20)
target_include_directories(mitra-gateway PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(mitra-gateway PRIVATE Drogon::Drogon)
