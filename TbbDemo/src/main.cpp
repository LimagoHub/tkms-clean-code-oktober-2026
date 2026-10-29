#include <oneapi/tbb/blocked_range.h>
#include <oneapi/tbb/global_control.h>
#include <oneapi/tbb/parallel_for.h>
#include <oneapi/tbb/parallel_reduce.h>

#include <chrono>
#include <cmath>
#include <iostream>
#include <vector>


int main() {
    constexpr std::size_t N = 50'000'000;
    std::vector<double> data(N);

    auto t0 = std::chrono::steady_clock::now();

    // Parallele Schleife: jedes Element unabhaengig berechnen
    tbb::parallel_for(tbb::blocked_range<std::size_t>(0, N),
        [&](const tbb::blocked_range<std::size_t>& r) {
            for (std::size_t i = r.begin(); i != r.end(); ++i)
                data[i] = std::sqrt(static_cast<double>(i)) * std::sin(static_cast<double>(i));
        });

    // Parallele Reduktion: Summe bilden
    double sum = tbb::parallel_reduce(
        tbb::blocked_range<std::size_t>(0, N), 0.0,
        [&](const tbb::blocked_range<std::size_t>& r, double acc) {
            for (std::size_t i = r.begin(); i != r.end(); ++i) acc += data[i];
            return acc;
        },
        [](double a, double b) { return a + b; });

    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                  std::chrono::steady_clock::now() - t0).count();

    std::cout << "Threads: " << tbb::global_control::active_value(
                     tbb::global_control::max_allowed_parallelism) << "\n"
              << "Summe:   " << sum << "\n"
              << "Zeit:    " << ms << " ms\n";
}
