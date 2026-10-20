#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <vector>
#include <functional>

class ThreadPool {
public:
    explicit ThreadPool(std::size_t count) : running_(true) {
        for (std::size_t i = 0; i < count; ++i) {
            threads_.emplace_back(&ThreadPool::workerLoop, this);
        }
    }

    ~ThreadPool() {
        {
            std::lock_guard lock{mutex_};
            running_ = false;
        }
        cv_.notify_all();
        for (auto& t : threads_) {
            if (t.joinable()) t.join();
        }
    }

    void submit(std::function<void()> task) {
        {
            std::lock_guard lock{mutex_};
            if (!running_) throw std::runtime_error("pool stopped");
            queue_.push(std::move(task));
        }
        cv_.notify_one();
    }

    std::uint64_t processed() const { return processed_.load(); }

private:
    void workerLoop() {
        while (true) {
            std::function<void()> task;
            {
                std::unique_lock lock{mutex_};
                cv_.wait(lock, [this] { return !queue_.empty() || !running_; });
                if (!running_ && queue_.empty()) return;
                task = std::move(queue_.front());
                queue_.pop();
            }
            task();
            ++processed_;
        }
    }

    std::queue<std::function<void()>> queue_;
    std::mutex mutex_;
    std::condition_variable cv_;
    std::vector<std::thread> threads_;
    std::atomic<bool> running_;
    std::atomic<std::uint64_t> processed_{0};
};

int main() {
    ThreadPool pool(4);
    for (int i = 0; i < 10; ++i) {
        pool.submit([i] {
            std::cout << "Task " << i << " executed in thread " << std::this_thread::get_id() << '\n';
        });
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout << "Processed: " << pool.processed() << " tasks\n";
    return 0;
}
