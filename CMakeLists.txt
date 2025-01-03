cmake_minimum_required(VERSION 3.24)
project(demo VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE PROJECT_INCLUDE_DIRS include/*.hpp)
add_executable(${PROJECT_NAME} src/main.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE include)

if (${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
    target_compile_options(${PROJECT_NAME} PRIVATE -fsanitize=address,undefined)
    target_link_libraries(${PROJECT_NAME} PRIVATE -fsanitize=address,undefined)
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNC")
    target_link_libraries(${PROJECT_NAME} PRIVATE stdc++exp)
endif()

target_compile_options(${PROJECT_NAME} PRIVATE
                            -std=c++26
                            -Wall
                            -Wextra
                            -pedantic
)