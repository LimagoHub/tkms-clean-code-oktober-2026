//
// Created by JoachimWagner on 10.04.2024.
//

#pragma once
#include <memory>
#include "../../AbstractVectorFactory.h"
#include "../../../generator/IGenerator.h"

namespace atlas::container {

    template<class T>
    class VectorFactorySequentialImpl : public AbstractVectorFactory<T> {
        using GeneratorPtr = std::unique_ptr<generator::IGenerator<T>>;
        GeneratorPtr generator_;

    public:
        explicit VectorFactorySequentialImpl(GeneratorPtr generator) : generator_{std::move(generator)} {}
        ~VectorFactorySequentialImpl() override = default;

    protected:
        auto fillVector(std::vector<T>& data) const noexcept -> void override {
            for (size_t i = 0; i < data.size(); ++i) {
                data[i] = generator_->next();
            }
        }
    };

}
