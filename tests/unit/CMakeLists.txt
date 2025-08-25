include(FetchContent)
FetchContent_Declare(
    GoogleTest
    GIT_REPOSITORY https://github.com/google/googletest
    GIT_TAG v1.16.0
    GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(GoogleTest)

set(UNIT_TEST unit_tests)

file(GLOB_RECURSE UNIT_TEST_SOURCES ./*.cpp)
message("Unit test sources: ${UNIT_TEST_SOURCES}")

add_executable(${UNIT_TEST} ${UNIT_TEST_SOURCES})

target_compile_options(${UNIT_TEST} PRIVATE -Wall -Wextra -pedantic -std=c++26)
target_include_directories(${UNIT_TEST} PRIVATE ../../include)
target_link_libraries(${UNIT_TEST} PRIVATE GTest::gtest_main)