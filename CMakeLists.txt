cmake_minimum_required(VERSION 3.0.0)
project(InventoryManagement 
        VERSION "1.0.0"
        DESCRIPTION "InventoryManagement")

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${InventoryManagement_SOURCE_DIR}/client/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${InventoryManagement_SOURCE_DIR}/client/bin)
set(APP_ICON_RESOURCE_WINDOWS ${InventoryManagement_SOURCE_DIR}/client/resources/appicon.rc)
set(VERSIONINFO ${InventoryManagement_SOURCE_DIR}/client/resources/versioninfo.rc)

file(GLOB_RECURSE IM_resources ${InventoryManagement_SOURCE_DIR}/client/resources/*.rc)
file(GLOB_RECURSE IM_resources_h ${InventoryManagement_SOURCE_DIR}/client/resources/*.h)
file(GLOB_RECURSE IM_src_cpp ${InventoryManagement_SOURCE_DIR}/client/src/*.cpp)
file(GLOB_RECURSE IM_src_h ${InventoryManagement_SOURCE_DIR}/client/src/*.h)

add_executable(InventoryManagement ${APP_ICON_RESOURCE_WINDOWS} ${VERSIONINFO} ${IM_resources_h} ${IM_resources} ${IM_src_cpp} ${IM_src_h})
target_link_libraries(InventoryManagement ${InventoryManagement_SOURCE_DIR}/client/curl/lib/libcurl.lib)
include_directories(${InventoryManagement_SOURCE_DIR}/client/curl/include)
include_directories(${InventoryManagement_SOURCE_DIR}/client/resources)
include_directories(${InventoryManagement_SOURCE_DIR}/client/src)

target_link_options(InventoryManagement PRIVATE /machine:x64)