cmake_minimum_required(VERSION 3.20)

project(PerformanceAnalysis
    VERSION 1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# VS Code’s CMake Tools extension automatically reads this file and updates IntelliSense include paths.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(MSVC)
    add_compile_options(/W4)
    # add_compile_options(/showIncludes)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

set(SOURCES
    src/branch.cpp
)
add_executable(PerformanceAnalysisExe ${SOURCES})