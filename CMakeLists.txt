cmake_minimum_required(VERSION 3.0.0)
project(SPTrade 
        VERSION 1.0.0
        DESCRIPTION "SPTrade")

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${SPTrade_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${SPTrade_SOURCE_DIR}/bin)

add_executable(SPTrade src/main.cpp src/api/api.cpp)
target_link_libraries(SPTrade ${SPTrade_SOURCE_DIR}/curl/lib/libcurl.lib)
include_directories(${SPTrade_SOURCE_DIR}/curl/include)
include_directories(${SPTrade_SOURCE_DIR}/src)

target_link_options(SPTrade PRIVATE /machine:x64)