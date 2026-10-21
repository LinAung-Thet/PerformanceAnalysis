cmake_minimum_required(VERSION 3.20)

project(PerformanceAnalysis
    VERSION 1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# VS Code’s CMake Tools extension automatically reads this file and updates IntelliSense include paths.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(MSVC)
    add_compile_options(/W4 /Zc:__cplusplus)
    # add_compile_options(/showIncludes)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

set(SOURCES
    src/branch.cpp
    src/false_sharing.cpp
    src/pointer_aliasing.cpp
)
add_executable(PerformanceAnalysisExe ${SOURCES})

target_compile_features(PerformanceAnalysisExe PRIVATE cxx_std_20)

# message(STATUS "CMAKE_CXX_STANDARD = ${CMAKE_CXX_STANDARD}")
# message(STATUS "CMAKE_CXX_FLAGS = ${CMAKE_CXX_FLAGS}")
# message(STATUS "CMAKE_CXX_FLAGS_RELEASE = ${CMAKE_CXX_FLAGS_RELEASE}")
# message(STATUS "CMAKE_CXX_FLAGS_DEBUG = ${CMAKE_CXX_FLAGS_DEBUG}")