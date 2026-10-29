#pragma once
#include <vector>
#include <thread>
#include <memory>
#include <utility>
#include "../../AbstractVectorFactory.h"
#include "../../../generator/IGeneratorFactory.h"

namespace atlas::container {

    template<class T>
    class VectorFactoryParallelImpl : public AbstractVectorFactory<T> {
        using GeneratorFactoryPtr = std::unique_ptr<atlas::generator::IGeneratorFactory<T>>;
        using ThreadVector = std::vector<std::thread>;

    public:
        VectorFactoryParallelImpl(GeneratorFactoryPtr generatorFactory, size_t threadCount)
            : generatorFactory_{std::move(generatorFactory)}, threadCount_{threadCount ? threadCount : 1} {}

    protected:
        void fillVector(std::vector<T>& vector) const noexcept override {
            if (vector.empty()) return;
            FillJob job{*this, vector};
            job.execute();
        }

    private:
        GeneratorFactoryPtr generatorFactory_;
        size_t threadCount_;

        class FillJob {
        public:
            FillJob(const VectorFactoryParallelImpl& factory, std::vector<T>& target)
                : factory_{factory}, target_{target}, partitionSize_{target_.size() / factory_.threadCount_} {}

            void execute() const {
                auto threads = createThreadHolder();
                addWorkersToThreads(threads);
                awaitThreadTermination(threads);
            }

        private:
            [[nodiscard]] ThreadVector createThreadHolder() const {
                ThreadVector holder;
                holder.reserve(factory_.threadCount_);
                return holder;
            }

            void addWorkersToThreads(ThreadVector& threads) const {
                for (size_t currentThread = 0; currentThread < factory_.threadCount_; ++currentThread) {
                    threads.emplace_back(&FillJob::workerByIndex, this, currentThread);
                }
            }

            void awaitThreadTermination(ThreadVector& threads) const {
                for (auto& t : threads) {
                    if (t.joinable()) t.join();
                }
            }

            void workerByIndex(size_t threadIndex) const {
                const auto [start, end] = calculatePartition(threadIndex);
                fillSegmentWorker(start, end);
            }

            void fillSegmentWorker(size_t const startIndex, size_t const endIndex) const {
                const auto generator = factory_.generatorFactory_->create();
                auto& data = target_;
                for (size_t i = startIndex; i < endIndex; ++i) {
                    data[i] = generator->next();
                }
            }

            [[nodiscard]] std::pair<size_t, size_t> calculatePartition(size_t threadIndex) const {
                const size_t start = threadIndex * partitionSize_;
                const size_t end = (threadIndex == factory_.threadCount_ - 1) ? target_.size() : start + partitionSize_;
                return {start, end};
            }

            const VectorFactoryParallelImpl& factory_;
            std::vector<T>& target_;
            const size_t partitionSize_;
        };
    };

}
