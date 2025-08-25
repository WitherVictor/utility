cmake_minimum_required(VERSION 3.21)
project(demo VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 添加单元测试
add_subdirectory(tests/unit)
add_subdirectory(tests/benchmark)

#  Main target begin
file(GLOB_RECURSE PROJECT_INCLUDE_DIRS include/*.hpp)
add_executable(${PROJECT_NAME} src/main.cpp)

target_compile_options(${PROJECT_NAME} PRIVATE
                            -std=c++26
                            -Wall
                            -Wextra
                            -pedantic
)

target_include_directories(${PROJECT_NAME} PRIVATE include)
#  Main target end

#  include stdc++exp for std::print under windows gnu
if (${CMAKE_CXX_COMPILER_ID} MATCHES "GNU" AND ${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    target_link_libraries(${PROJECT_NAME} PRIVATE stdc++exp)
endif()