# 3.10.0 or later is required for cmake issue #16482 to support MSVC `/std:` flag
# 3.11.0 or later is required to use FetchContent https://cliutils.gitlab.io/modern-cmake/chapters/projects/fetch.html
cmake_minimum_required(VERSION 3.11.0)
enable_language(CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/../cmake/modules)
set(CMAKE_CXX_STANDARD_REQUIRED ON) #...is required...
set(CMAKE_CXX_EXTENSIONS OFF) #...without compiler extensions like gnu++11

# ref: https://github.com/HowardHinnant/date/pull/545
option(HAS_UNCAUGHT_EXCEPTIONS "has C++17 uncaught_exceptions()" 1)

#
# Get dependencies
#
include( FetchContent )
FetchContent_Declare( date_src
    GIT_REPOSITORY https://github.com/HowardHinnant/date.git
    GIT_TAG        v3.0.0  # adjust tag/branch/commit as needed
)
FetchContent_MakeAvailable(date_src)


set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake/modules)
project(apache2_log_analyzer)
add_subdirectory(test)

#
# Source files
#
set(apache2_log_analyzer_src
    "./src/main.cpp"
)

#
# Update compiler waring flags
#
if(MSVC AND NOT "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    # Force to always compile with W4
    if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
        string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    endif()
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    # Update if necessary
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wno-long-long -pedantic")
endif()

#
# Compile
#
add_executable(apache2_log_analyzer ${apache2_log_analyzer_src})
if (HAS_UNCAUGHT_EXCEPTIONS)
    add_compile_definitions(HAS_UNCAUGHT_EXCEPTIONS=1)
endif()

#
# Link
#
target_link_libraries (apache2_log_analyzer date::date)
