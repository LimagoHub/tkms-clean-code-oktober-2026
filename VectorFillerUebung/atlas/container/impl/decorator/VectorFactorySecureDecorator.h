//
// Created by JoachimWagner on 12.03.2025.
//

#pragma once
#include <memory>
#include <iostream>
#include "../../IVectorFactory.h"

namespace atlas::container {

    template<class T>
    class VectorFactorySecureDecorator : public IVectorFactory<T> {
        using VectorPtr = std::unique_ptr<std::vector<T>>;
        using FactoryPtr = std::unique_ptr<IVectorFactory<T>>;

    public:
        explicit VectorFactorySecureDecorator(FactoryPtr vectorFactory)
            : vectorFactory_{std::move(vectorFactory)} {}

        auto createAndFillVector(const size_t size) -> VectorPtr override {
            std::cout << "Du kommst hier rein!" << std::endl;
            return vectorFactory_->createAndFillVector(size);
        }

    private:
        FactoryPtr vectorFactory_;
    };

}
