cmake_minimum_required(VERSION 3.21)
project(demo VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 导出接口库
add_library(util INTERFACE)

# 添加库路径
target_include_directories(util INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# 至少需要 C++23
target_compile_features(util INTERFACE
    cxx_std_23
)

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

# 添加单元测试
add_subdirectory(tests/unit_test)
add_subdirectory(tests/benchmark)