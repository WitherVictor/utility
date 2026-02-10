# 启用测试
enable_testing()

# 引入 FetchContent 下载 google test
include(FetchContent)
FetchContent_Declare(
    google_test
    GIT_REPOSITORY https://github.com/google/googletest
    GIT_TAG v1.17.0
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(google_test)

# 添加所有单元测试文件
add_executable(unit_test
    gcd_unittest.cpp
    rng_coro_unittest.cpp
    rng_unittest.cpp
    roll_dice_unittest.cpp
    sqrt_newton_unittest.cpp
    thread_pool_unittest.cpp
)

# 启用所有警告，禁用扩展
# 将警告视为错误
target_compile_options(unit_test PRIVATE
    -Wall
    -Wextra
    -pedantic
    -Werror
)

# 链接 gtest 库与被测试的头文件库
target_link_libraries(unit_test PRIVATE
    util
    gtest
    gtest_main
)

# 引入 GoogleTest 来自动注册单元测试
include(GoogleTest)

# 自动注册单元测试到 ctest
gtest_discover_tests(unit_test)
