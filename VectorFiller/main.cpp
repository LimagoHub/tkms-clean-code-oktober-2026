#include <iostream>
#include <climits>
#include <chrono>
#include <vector>
#include <memory>
#include <algorithm>
#include <thread>

int main() {
    const size_t collection_size = INT32_MAX / 2;

    auto feld = std::make_shared<std::vector<int>>(collection_size);
    std::cout << "Running..." << std::endl;

    auto start_ = std::chrono::high_resolution_clock::now();

    for (int  i = 0; i < collection_size ; ++i) {
        feld->at(i) = rand();
    }

    auto end_ = std::chrono::high_resolution_clock::now();
    std::cout << "Duration: " << std::chrono::duration_cast<std::chrono::milliseconds>(end_-start_).count() << std::endl;

    // shared_ptr<vector<int>> CreateAndFillVector(size_t size)
    return 0;
}
