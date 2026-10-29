#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

class TDemo {
private:
    inline static size_t threadCount{5};
    std::vector<std::thread> threadHolder_;
public:
    explicit TDemo() = default;
    ~TDemo() = default;

    auto run() -> void {

        threadHolder_.reserve(threadCount);
        for (size_t i = 0; i < threadCount; ++i) {
            // Partition berechnen
            threadHolder_.emplace_back(&TDemo::worker,this, i, 1000);
        }
        for(auto & thread : threadHolder_) {
            thread.join();
        }
        std::cout << "Alle Threads beendet" << std::endl;
    }

    auto worker(int id, size_t duration) -> void {
        // eigene instanz  generator
        std::this_thread::sleep_for(std::chrono::milliseconds(duration));
        std::cout << "Thread Nr. " << id << " terminated" << std::endl;
    }
};

int main() {
    TDemo demo;
    demo.run();
    return 0;
}