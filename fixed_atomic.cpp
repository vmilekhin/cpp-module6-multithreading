#include <iostream>
#include <thread>
#include <atomic>

std::atomic<int> counter{0};

void worker() {
    for (int i = 0; i < 1000000; ++i) {
        ++counter;
    }
}

int main() {
    std::thread a{worker};
    std::thread b{worker};
    a.join();
    b.join();
    std::cout << "fixed_atomic result: " << counter.load() << " (expected 2000000)\n";
    return 0;
}
