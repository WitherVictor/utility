# 使用 FetchContent 下载依赖 google benchmark
include(FetchContent)
FetchContent_Declare(
    google_benchmark
    GIT_REPOSITORY https://github.com/google/benchmark
    GIT_TAG v1.9.5
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(google_benchmark)

# 收集 benchmark 源文件
add_executable(bm_test
    gcd_bm.cpp
    sqrt_newton_bm.cpp
)

# 设置可执行文件的编译参数
target_compile_options(bm_test PRIVATE
    -std=c++26
    -Wall
    -Wextra
    -pedantic
    -O2
)

# 目标链接的 benchmark 库
target_link_libraries(bm_test
    PRIVATE
        util
        benchmark::benchmark
        benchmark::benchmark_main
)
