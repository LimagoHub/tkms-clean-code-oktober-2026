#include <iostream>
#include "threadpool/thread_pool.hpp"

int main()
{
    synced_stream sync_out;
    thread_pool pool;

    sync_out.println("Thread pool created with ", pool.get_thread_count(), " threads.");

    // Submit tasks with return values
    auto future1 = pool.submit([] { return 6 * 7; });
    auto future2 = pool.submit([] { return 100 + 23; });

    sync_out.println("6 * 7 = ", future1.get());
    sync_out.println("100 + 23 = ", future2.get());

    // Parallelize a loop
    std::vector<int> results(10, 0);
    pool.parallelize_loop(0, 9, [&results](int i) {
        results[i] = i * i;
    });

    sync_out.print("Squares: ");
    for (int i = 0; i < 10; i++)
        sync_out.print(results[i], (i < 9 ? ", " : "\n"));

    return 0;
}
