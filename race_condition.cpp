#include <iostream>
#include <thread>

int counter = 0;

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
    std::cout << "race_condition result: " << counter << " (expected 2000000)\n";
    return 0;
}
