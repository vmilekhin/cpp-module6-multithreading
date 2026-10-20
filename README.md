
# Module 6: Multithreading and Synchronization (C++20)

Практическая работа по обнаружению гонок данных (data races) и проектированию потокобезопасных компонентов.

## Что сделано
1. Data Race: Демонстрация несинхронизированного инкремента счетчика из двух потоков. Результат меньше ожидаемого (undefined behavior).
2. Mutex: Исправление через std::mutex и std::lock_guard. Результат стабильно корректный.
3. Atomic: Исправление через std::atomic<int>. Работает быстрее мьютекса для простых операций.
4. ThreadPool: Реализован потокобезопасный пул задач на std::queue, std::mutex, std::condition_variable и std::atomic (архитектура SADER).

## Сборка и запуск
g++ -std=c++20 -pthread race_condition.cpp -o race_condition
g++ -std=c++20 -pthread fixed_mutex.cpp -o fixed_mutex
g++ -std=c++20 -pthread fixed_atomic.cpp -o fixed_atomic
g++ -std=c++20 -pthread thread_pool.cpp -o thread_pool

./race_condition
./fixed_mutex
./fixed_atomic
./thread_pool
