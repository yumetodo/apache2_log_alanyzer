﻿# 3.10.0 or later is required for cmake issue #16482 to support MSVC `/std:` flag
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

#
# Config options
#
if((CMAKE_BUILD_TYPE STREQUAL "Debug") AND ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU"))
    message("you can specify APACHE2_LOG_ANALYZER_ENABLE_COVERAGE")
    option(APACHE2_LOG_ANALYZER_ENABLE_COVERAGE "enable coverage" FALSE)
else()
    set(APACHE2_LOG_ANALYZER_ENABLE_COVERAGE FALSE)
endif()

#
# Set our project name
#
project(basic_test)

#
# Source files
#
set(basic_test_src
    "./test.cpp"
    "./cmd_argument_parser.cpp"
    "./line_splitter.cpp"
    "./date_parser.cpp"
    "./count_by_hour.cpp"
    "./count_by_remote.cpp"
)

if(APACHE2_LOG_ANALYZER_ENABLE_COVERAGE)
    message("coverage enabled")
    include(CodeCoverage)
    APPEND_COVERAGE_COMPILER_FLAGS()
    set(COVERAGE_EXCLUDES "*gcc*" "*iutest*" "*/usr/include/*" "*mingw*")
    SETUP_TARGET_FOR_COVERAGE(
        NAME test_coverage       # New target name
        EXECUTABLE basic_test          # Executable in PROJECT_BINARY_DIR
        DEPENDENCIES basic_test        # Dependencies to build first
    )
    option(APACHE2_LOG_ANALYZER_ENABLE_COVERAGE_HTML "enable coverage result to html" TRUE)
    option(APACHE2_LOG_ANALYZER_ENABLE_COVERAGE_SEND "send coverage result" FALSE)
    if(APACHE2_LOG_ANALYZER_ENABLE_COVERAGE_HTML)
        message("coverage result to html enabled")
        SETUP_TARGET_FOR_COVERAGE_TO_HTML(
            NAME test_coverage_to_html                 # New target name
            INFO_FILE_NAME test_coverage.info.cleaned  # coverage task result file name
            DEPENDENCIES test_coverage                 # Dependencies(coverage task, etc...)
        )
    endif()
endif()

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
add_executable(basic_test ${basic_test_src})
if (HAS_UNCAUGHT_EXCEPTIONS)
    add_compile_definitions(HAS_UNCAUGHT_EXCEPTIONS=1)
endif()

#
# Link
#
target_link_libraries (basic_test date::date)
if(WIN32)
    target_link_libraries(basic_test ws2_32)
endif()

add_custom_target(run_test
    COMMAND basic_test
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
    DEPENDS basic_test
    COMMENT "Execute produced executable."
)
