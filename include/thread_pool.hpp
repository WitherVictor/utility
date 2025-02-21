#pragma once

#include <concepts>
#include <functional>
#include <future>
#include <memory>
#include <mutex>
#include <stop_token>
#include <thread>
#include <queue>
#include <condition_variable>

class thread_pool {
public:
    thread_pool(std::size_t thread_count = std::thread::hardware_concurrency())
        : m_queue_mutex{}, m_queue_cv{}, m_queue{}, m_threads(thread_count) 
    {
        for (auto& thread : m_threads) {
            thread = std::jthread([this](std::stop_token stop_token) {
                while (true) {
                    std::unique_lock lock{m_queue_mutex};

                    //  存在谓词的 wait() 在谓词返回 true 时直接跳过阻塞
                    //  因此线程池析构时队列若存在多个任务，不会导致死锁
                    m_queue_cv.wait(lock, [this, &stop_token]() {
                        return !m_queue.empty() || stop_token.stop_requested(); });

                    if (stop_token.stop_requested() && m_queue.empty())
                        return;

                    auto task = std::move(m_queue.front());
                    m_queue.pop();
                    lock.unlock();
                    
                    task();
                }
            });
        }
    }

    ~thread_pool() {
        for (auto& thread : m_threads)
            thread.request_stop();

        m_queue_cv.notify_all();
    }

    template <typename Func, typename... Args>
    requires std::invocable<Func, Args...>
    auto submit(Func&& func, Args&&... args) {
        using return_type = std::invoke_result_t<Func, Args...>;

        //  包装任务为 std::packaged_task<return_type()>
        //  并用 std::make_unique() 包装 std::packaged_task<return_type()> 放在堆上
        auto task = std::make_unique<std::packaged_task<return_type()>>(
            [func = std::forward<Func>(func), ...args = std::forward<Args>(args)]() mutable {
                return std::invoke(func, args...);
            }
        );

        auto result_future = task->get_future();

        std::unique_lock lock{m_queue_mutex};
        //  再用 lambda 包装 std::packaged_task<return_type()> 擦除其类型为 void()
        //  并放入队列中
        m_queue.emplace(std::move([task = std::move(task)]() mutable { (*task)(); }));
        lock.unlock();

        m_queue_cv.notify_one();
        
        return result_future;
    }

private:
    mutable std::mutex m_queue_mutex;
    std::condition_variable m_queue_cv;
    std::queue<std::move_only_function<void()>> m_queue;

    //  在通知工作所有线程后，析构函数体执行完毕
    //  接下来会以声明的逆序销毁成员变量
    //  而析构 jthread 会自动调用 join()，因此无需手动 join()
    std::vector<std::jthread> m_threads;
};