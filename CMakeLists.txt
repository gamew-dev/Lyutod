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
# Mostly, you dont need to add the .h files, but
# since many text editor/IDE doesn't show it in
# project tree, I just add it here anyway
file(GLOB_RECURSE CORE_SRC
    src/core/*.h
    src/core/*.cpp
)

file(GLOB_RECURSE CMD_SRC
    src/command/*.h
    src/command/*.cpp
)

file(GLOB_RECURSE STATE_SRC
    src/state/*.h
    src/state/*.cpp
)

file(GLOB_RECURSE RESP_SRC
    src/responses/*.h
    src/responses/*.cpp
)

set(SRC_FILES
    ${CORE_SRC}
    ${CMD_SRC}
    ${STATE_SRC}
    ${RESP_SRC}
    src/main.cpp
)

# === Executable ===
# target output: "bot"
add_executable(bot ${SRC_FILES})

# === Include directories ===
# header files and implementation files base directory path
target_include_directories(bot PRIVATE
    ${PROJECT_SOURCE_DIR}/src
)

# === Link DPP library ===
# please note that i use .deb instalation instead
# of using src/include/
target_link_libraries(bot PRIVATE dpp)

# === Compiler warnings ===
target_compile_options(bot PRIVATE -Wall -Wextra -Wpedantic)
