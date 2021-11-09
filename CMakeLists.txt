cmake_minimum_required(VERSION 3.0.0)
project(InventoryManagement 
        VERSION 1.0.0
        DESCRIPTION "InventoryManagement")

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${InventoryManagement_SOURCE_DIR}/client/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${InventoryManagement_SOURCE_DIR}/clientbin)

file(GLOB_RECURSE IM_src_cpp ${InventoryManagement_SOURCE_DIR}/client/src/*.cpp)
file(GLOB_RECURSE IM_src_h ${InventoryManagement_SOURCE_DIR}/client/src/*.h)

add_executable(InventoryManagement ${IM_src_cpp} ${IM_src_h})
target_link_libraries(InventoryManagement ${InventoryManagement_SOURCE_DIR}/client/curl/lib/libcurl.lib)
include_directories(${InventoryManagement_SOURCE_DIR}/client/curl/include)
include_directories(${InventoryManagement_SOURCE_DIR}/client/src)

target_link_options(InventoryManagement PRIVATE /machine:x64)