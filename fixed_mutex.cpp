#include <iostream>
#include <thread>
#include <mutex>

std::mutex counter_mutex;
int counter = 0;

void worker() {
    for (int i = 0; i < 1000000; ++i) {
        std::lock_guard lock{counter_mutex};
        ++counter;
    }
}

int main() {
    std::thread a{worker};
    std::thread b{worker};
    a.join();
    b.join();
    std::cout << "fixed_mutex result: " << counter << " (expected 2000000)\n";
    return 0;
}
