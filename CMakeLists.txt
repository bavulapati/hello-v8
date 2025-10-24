cmake_minimum_required(VERSION 3.23)
project(hello)

if(NOT APPLE)
  message(FATAL_ERROR "This project is only tested on MacOS.")
endif()
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

add_executable(hello)
target_sources(hello
  PRIVATE
    hello.cc
)

target_compile_definitions(hello
  PRIVATE
    V8_COMPRESS_POINTERS
    V8_ENABLE_SANDBOX
)
find_package(V8 REQUIRED)
message(STATUS "V8_INCLUDE_DIR ${V8_INCLUDE_DIR}")
include_directories(${V8_INCLUDE_DIR})

target_link_libraries(hello ${V8_LIBS})


add_executable(logger)
target_sources(logger
  PRIVATE
    logger.cc
)

target_compile_definitions(logger
  PRIVATE
    V8_COMPRESS_POINTERS
    V8_ENABLE_SANDBOX
)

target_link_libraries(logger ${V8_LIBS})
