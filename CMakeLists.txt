cmake_minimum_required(VERSION 3.10)
project(LyutodBot VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0")

# === Source files ===
# .h and .cpp file for source code
file(GLOB_RECURSE SRC_FILES
    src/core/*.cpp
    src/core/*.h
    src/command/*.cpp
    src/command/*.h
    src/responses/*.h
    src/main.cpp
)

# === Executable ===
# target output: "bot"
add_executable(bot ${SRC_FILES}
    src/command/base_commands_ui.h)

# === Include directories ===
# file header
target_include_directories(bot PRIVATE
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/src/core
    ${PROJECT_SOURCE_DIR}/src/core/bothandler
    ${PROJECT_SOURCE_DIR}/src/core/config
    ${PROJECT_SOURCE_DIR}/src/core/terminal
    ${PROJECT_SOURCE_DIR}/src/core/utils
    ${PROJECT_SOURCE_DIR}/src/command
    ${PROJECT_SOURCE_DIR}/src/responses
    /usr/include
    /usr/local/include
)

# === Link DPP library ===
# please note that i use .deb instalation instead
# of using src/include/
target_link_libraries(bot PRIVATE dpp)

# === Compiler warnings ===
target_compile_options(bot PRIVATE -Wall -Wextra -Wpedantic)
