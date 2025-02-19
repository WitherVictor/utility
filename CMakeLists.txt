cmake_minimum_required(VERSION 3.21)
project(demo VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

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

#  Unit test target begin
set(UNIT_TEST unit-tests)

add_subdirectory(thirdparty/google-test)

file(GLOB_RECURSE UNIT_TEST_SOURCES unit-tests/*.cpp)
message("Unit test sources: ${UNIT_TEST_SOURCES}")

add_executable(${UNIT_TEST} ${UNIT_TEST_SOURCES})

target_compile_options(${UNIT_TEST} PRIVATE -Wall -Wextra -pedantic -std=c++26)
target_include_directories(${UNIT_TEST} PRIVATE include)
target_link_libraries(${UNIT_TEST} PRIVATE GTest::gtest_main)
#  Unit test target end