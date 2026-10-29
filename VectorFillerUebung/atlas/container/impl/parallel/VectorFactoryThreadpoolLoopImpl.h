#pragma once
#include <memory>
#include "../../AbstractVectorFactory.h"
#include "../../../generator/IGeneratorFactory.h"
#include "../../../threadpool/thread_pool.hpp"

namespace atlas::container {

    template<class T>
    class VectorFactoryThreadpoolLoopImpl : public AbstractVectorFactory<T> {
        using GeneratorFactoryPtr = std::unique_ptr<generator::IGeneratorFactory<T>>;

        GeneratorFactoryPtr generatorFactory_;
        mutable threadpool::thread_pool pool_;

    public:
        explicit VectorFactoryThreadpoolLoopImpl(GeneratorFactoryPtr generatorFactory,
                                                 uint32_t threadCount = std::thread::hardware_concurrency())
            : generatorFactory_{std::move(generatorFactory)}, pool_{threadCount} {}

        ~VectorFactoryThreadpoolLoopImpl() override = default;

    protected:
        void fillVector(std::vector<T>& data) const noexcept override {
            if (data.empty()) return;

            pool_.parallelize_loop(size_t{0}, data.size() - 1,
                [this, &data](size_t i) {
                    thread_local auto generator = generatorFactory_->create();
                    data[i] = generator->next();
                });
        }
    };

}
