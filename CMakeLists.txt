cmake_minimum_required(VERSION 3.0.0)
project(InventoryManagement 
        VERSION 1.0.0
        DESCRIPTION "InventoryManagement")

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${InventoryManagement_SOURCE_DIR}/client/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${InventoryManagement_SOURCE_DIR}/clientbin)

add_executable(InventoryManagement client/src/main.cpp client/src/api/api.cpp)
target_link_libraries(InventoryManagement ${InventoryManagement_SOURCE_DIR}/client/curl/lib/libcurl.lib)
include_directories(${InventoryManagement_SOURCE_DIR}/client/curl/include)
include_directories(${InventoryManagement_SOURCE_DIR}/client/src)

target_link_options(InventoryManagement PRIVATE /machine:x64)