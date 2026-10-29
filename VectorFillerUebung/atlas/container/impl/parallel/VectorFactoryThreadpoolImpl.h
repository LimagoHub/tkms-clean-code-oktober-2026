#pragma once
#include <memory>
#include <vector>
#include <future>
#include "../../AbstractVectorFactory.h"
#include "../../../generator/IGeneratorFactory.h"
#include "../../../threadpool/thread_pool.hpp"

namespace atlas::container {

    template<class T>
    class VectorFactoryThreadpoolImpl : public AbstractVectorFactory<T> {
        using GeneratorFactoryPtr = std::unique_ptr<generator::IGeneratorFactory<T>>;
        using FutureVector = std::vector<std::future<bool>>;

        GeneratorFactoryPtr generatorFactory_;
        mutable threadpool::thread_pool pool_;

    public:
        explicit VectorFactoryThreadpoolImpl(GeneratorFactoryPtr generatorFactory,
                                             uint32_t threadCount = std::thread::hardware_concurrency())
            : generatorFactory_{std::move(generatorFactory)}, pool_{threadCount} {}

        ~VectorFactoryThreadpoolImpl() override = default;

    protected:
        void fillVector(std::vector<T>& data) const noexcept override {
            if (data.empty()) return;

            const size_t size = data.size();
            const auto numTasks = pool_.get_thread_count();
            const size_t blockSize = size / numTasks;

            FutureVector futures;
            futures.reserve(numTasks);

            for (uint32_t t = 0; t < numTasks; ++t) {
                const size_t start = t * blockSize;
                const size_t end = (t == numTasks - 1) ? size : start + blockSize;
                auto generator = std::shared_ptr<generator::IGenerator<T>>(generatorFactory_->create());

                futures.emplace_back(pool_.submit([&data, start, end, generator]() {
                    for (size_t i = start; i < end; ++i) {
                        data[i] = generator->next();
                    }
                }));
            }

            for (auto& f : futures) {
                f.wait();
            }
        }
    };

}
