//
// Created by JoachimWagner on 10.04.2024.
//

#pragma once
#include <memory>
#include <algorithm>
#include <execution>
#include "../../AbstractVectorFactory.h"
#include "../../../generator/IGeneratorFactory.h"

namespace atlas::container {

    template<class T>
    class VectorFactoryAutoImpl : public AbstractVectorFactory<T> {
        using GeneratorFactoryPtr = std::unique_ptr<generator::IGeneratorFactory<T>>;
        GeneratorFactoryPtr generatorFactory_;

    public:
        explicit VectorFactoryAutoImpl(GeneratorFactoryPtr generatorFactory) : generatorFactory_{std::move(generatorFactory)} {}
        ~VectorFactoryAutoImpl() override = default;

    protected:
        auto fillVector(std::vector<T>& vector) const noexcept -> void override {
            std::for_each(std::execution::par, vector.begin(), vector.end(),
                [builder = generatorFactory_.get()](T& value) {
                    thread_local auto generator = builder->create();
                    value = generator->next();
                });
        }
    };

}
