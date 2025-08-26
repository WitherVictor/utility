set(BENCHMARK ${PROJECT_NAME}_benchmark)

include(FetchContent)
FetchContent_Declare(
    google_benchmark
    GIT_REPOSITORY https://github.com/google/benchmark
    GIT_TAG v1.9.4
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(google_benchmark)

file(GLOB_RECURSE BENCHMARK_SOURCES *.cpp)
message("Benchmark sources: ${BENCHMARK_SOURCES}")

add_executable(${BENCHMARK} ${BENCHMARK_SOURCES})

target_compile_options(${BENCHMARK}
    PRIVATE
        -std=c++26
        -Wall
        -Wextra
        -pedantic
        -O2
)

target_include_directories(${BENCHMARK}
    PRIVATE
        ../../include
)

target_link_libraries(${BENCHMARK}
    PRIVATE
        benchmark::benchmark
        benchmark::benchmark_main
)