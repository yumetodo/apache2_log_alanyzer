# for cmake issue #16482 to support MSVC `/std:` flag
cmake_minimum_required(VERSION 3.10.0)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake/modules)
project(apache2_log_analyzer)
add_subdirectory(test)
