# 引入 FetchContent 下载 google test
include(FetchContent)
FetchContent_Declare(
    google_test
    GIT_REPOSITORY https://github.com/google/googletest
    GIT_TAG v1.17.0
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(google_test)

# 收集源文件
set(UNITTEST_SOURCES
    gcd_unittest.cpp
    rng_coro_unittest.cpp
    rng_unittest.cpp
    roll_dice_unittest.cpp
    sqrt_newton_unittest.cpp
    thread_pool_unittest.cpp
)

# 迭代每一个源文件
foreach(UNITTEST_SOURCE ${UNITTEST_SOURCES})
    # 提取单元测试文件的无扩展名无目录的纯文件名
    get_filename_component(UNITTEST_NAME ${UNITTEST_SOURCE} NAME_WE)

    # 使用纯文件名作为目标，并添加可执行文件
    add_executable(${UNITTEST_NAME} ${UNITTEST_SOURCE})

    # 为目标添加编译参数
    target_compile_options(${UNITTEST_NAME}
        PRIVATE
            -Wall -Wextra -pedantic -std=c++26
    )

    # 指定目标包含头文件路径
    target_include_directories(${UNITTEST_NAME}
        PRIVATE
            ../../include
    )

    # 为目标链接库
    target_link_libraries(${UNITTEST_NAME}
        PRIVATE
            GTest::gtest_main
    )
endforeach()
