# 使用 FetchContent 下载依赖 google benchmark
include(FetchContent)
FetchContent_Declare(
    google_benchmark
    GIT_REPOSITORY https://github.com/google/benchmark
    GIT_TAG v1.9.4
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(google_benchmark)

# 收集 benchmark 源文件
set(BENCHMARK_SOURCES
    gcd_bm.cpp
    sqrt_newton_bm.cpp
)

# 遍历所有 benchmark 源文件
foreach(BENCHMARK_SOURCE ${BENCHMARK_SOURCES})
    # 获取源文件名
    get_filename_component(BENCHMARK_NAME ${BENCHMARK_SOURCE} NAME_WE)

    # 以源文件名为目标创建可执行文件
    add_executable(${BENCHMARK_NAME} ${BENCHMARK_SOURCE})

    # 设置可执行文件的编译参数
    target_compile_options(${BENCHMARK_NAME}
        PRIVATE
            -std=c++26
            -Wall
            -Wextra
            -pedantic
            -O2
    )

    # 目标包括的头文件路径
    target_include_directories(${BENCHMARK_NAME}
        PRIVATE
            ../../include
    )

    # 目标链接的 benchmark 库
    target_link_libraries(${BENCHMARK_NAME}
        PRIVATE 
            benchmark::benchmark
            benchmark::benchmark_main
    )
endforeach()
